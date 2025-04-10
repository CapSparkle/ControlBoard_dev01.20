//###########################################################################
//
// FILE:   F2802x_Examples.h
//
// TITLE:  F2802x Device Definitions.
//
//###########################################################################
// $TI Release: F2802x Support Library v230 $
// $Release Date: Fri May  8 07:43:05 CDT 2015 $
// $Copyright: Copyright (C) 2008-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef F2802x_EXAMPLES_H
#define F2802x_EXAMPLES_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
      Specify System and Input clock frequency values.
-----------------------------------------------------------------------------*/
#ifndef SYSCLK
#define SYSCLK              60e6 // 60 Mhz CPU Freq (10 MHz input freq)
#endif

#ifndef CLKIN
#define CLKIN               10e6
#endif

/*-----------------------------------------------------------------------------
      Main interrupt parameters.
-----------------------------------------------------------------------------*/
#define ISR_PERIOD          (SYSCLK / MAIN_ISR_FREQ)
#define CPUL_GAIN           (int32)(100.0 * (1L<<21) / ISR_PERIOD)

#define MAIN_ISR_GROUP   	((Uint16)((MAIN_ISR_VEC - 0x20) >> 3))
#define MAIN_ISR_INDEX   	((Uint16)((MAIN_ISR_VEC - 0x20) & 0x7))

#define CalcCpuLoad(Timer)	((CPUL_GAIN * (-(Uint16)(Timer))) >> 21)


/*-----------------------------------------------------------------------------
      Specify the PLL control register (PLLCR) and divide select (DIVSEL) value.
-----------------------------------------------------------------------------*/
#ifndef DSP28_DIVFACTOR
#define DSP28_DIVFACTOR     2
#endif

#if (DSP28_DIVFACTOR == 4)
#define DSP28_DIVSEL        1 // Enable /4 for SYSCKOUT
#elif (DSP28_DIVFACTOR == 2)
#define DSP28_DIVSEL        2 // Enable /2 for SYSCLKOUT
#else
#define DSP28_DIVSEL        3 // Enable /1 for SYSCLKOUT
#endif

#define DSP28_PLLCR         (SYSCLK * DSP28_DIVFACTOR / CLKIN)


/*-----------------------------------------------------------------------------
      Specify the clock rate of the CPU (SYSCLKOUT) in nS.

      Take into account the input clock frequency and the PLL multiplier
      selected in step 1.

      Use one of the values provided, or define your own.
      The trailing L is required tells the compiler to treat
      the number as a 64-bit value.

      Only one statement should be uncommented.

      Example 1: 40 MHz devices:
                 CLKIN is a 10 MHz crystal or internal 10 MHz oscillator

                 In step 1 the user specified PLLCR = 0x8 for a
                 40 MHz CPU clock (SYSCLKOUT = 40 MHz).

                 In this case, the CPU_RATE will be 25.000L
                 Uncomment the line: #define CPU_RATE 25.000L

      Example 1: 50 MHz devices:
                 CLKIN is a 10 MHz crystal or internal 10 MHz oscillator

                 In step 1 the user specified PLLCR = 0xA for a
                 50 MHz CPU clock (SYSCLKOUT = 50 MHz).

                 In this case, the CPU_RATE will be 20.000L
                 Uncomment the line: #define CPU_RATE 20.000L


      Example 2: 60 MHz devices:
                 CLKIN is a 10 MHz crystal or internal 10 MHz oscillator

                 In step 1 the user specified PLLCR = 0xC for a
                 60 MHz CPU clock (SYSCLKOUT = 60 MHz).

                 In this case, the CPU_RATE will be 16.667L
                 Uncomment the line: #define CPU_RATE 16.667L

-----------------------------------------------------------------------------*/
#define CPU_RATE    ( 1000.0 / (SYSCLK/1e6) )
//----------------------------------------------------------------------------


/*-----------------------------------------------------------------------------
      Target device (in F2802x_Device.h) determines CPU frequency
      (for examples) - either 60 MHz (for 28026 and 28027), 50 MHz
      (for 28023 and 28023, or 40 MHz (for 28021, 28020, and 280200).
      User does not have to change anything here.
-----------------------------------------------------------------------------*/
#if (DSP28_28026PT||DSP28_28026DA||DSP28_28027PT||DSP28_28027DA)    // 28026||28027 devices only
  #define CPU_FRQ_60MHZ    1     // 60 Mhz CPU Freq (10 MHz input clock)
  #define CPU_FRQ_50MHZ    0
  #define CPU_FRQ_40MHZ    0
#elif (DSP28_28023PT||DSP28_28023DA||DSP28_28022PT||DSP28_28022DA) // 28023||28023 devices
  #define CPU_FRQ_60MHZ    0
  #define CPU_FRQ_50MHZ    1     // 50 MHz CPU Freq (10 MHz input clock)
  #define CPU_FRQ_40MHZ    0
#else                            // 28021||28020||280200 devices
  #define CPU_FRQ_60MHZ    1
  #define CPU_FRQ_50MHZ    0
  #define CPU_FRQ_40MHZ    0     // 40 MHz CPU Freq (10 MHz input clock)
#endif


// The following pointer to a function call calibrates the ADC and internal oscillators
#define Device_cal (void   (*)(void))0x3D7C80

//---------------------------------------------------------------------------
// Include Example Header Files:
//

#include "f2802x_globalprototypes.h"         // Prototypes for global functions within the .c files.
#include "f2802x_epwm_defines.h"             // Macros used for PWM examples.

#define PARTNO_28027PT  0xCF
#define PARTNO_28027DA  0xCE
#define PARTNO_28026PT  0xC7
#define PARTNO_28026DA  0xC6
#define PARTNO_28023PT  0xCD
#define PARTNO_28023DA  0xCC
#define PARTNO_28022PT  0xC5
#define PARTNO_28022DA  0xC4
#define PARTNO_28021PT  0xCB
#define PARTNO_28021DA  0xCA
#define PARTNO_28020PT  0xC3
#define PARTNO_28020DA  0xC2
#define PARTNO_280200PT 0xC1
#define PARTNO_280200DA 0xC0

// Include files not used with DSP/BIOS
#ifndef DSP28_BIOS
#include "f2802x_defaultisr.h"
#endif

// DO NOT MODIFY THIS LINE.
#define DELAY_US(A)  DSP28x_usDelay(((((long double) A * 1000.0L) / (long double)CPU_RATE) - 9.0L) / 5.0L)

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of F2802x_EXAMPLES_H definition

//===========================================================================
// End of file.
//===========================================================================
