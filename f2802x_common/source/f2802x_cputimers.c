//###########################################################################
//
// FILE:    F2802x_CpuTimers.c
//
// TITLE:    CPU 32-bit Timers Initialization & Support Functions.
//
// NOTES:   CpuTimer2 is reserved for use with DSP BIOS and
//          other realtime operating systems.
//
//          Do not use this timer in your application if you ever plan
//          on integrating DSP-BIOS or another realtime OS.
//
//###########################################################################
// $TI Release: F2802x Support Library v230 $
// $Release Date: Fri May  8 07:43:05 CDT 2015 $
// $Copyright: Copyright (C) 2008-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "F2802x_Device.h"     // Headerfile Include File
#include "f2802x_examples.h"   // Examples Include File


//---------------------------------------------------------------------------
// ConfigCpuTimer:
//---------------------------------------------------------------------------
void ConfigCpuTimer(volatile struct CPUTIMER_REGS *Regs, Uint32 Period, Uint16 IntEnable)
{
    // Initialize timer period:
    Regs->PRD.all = Period;

    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    Regs->TPR.all  = 0;
    Regs->TPRH.all  = 0;

    // Initialize timer control register:
    Regs->TCR.bit.TSS = 1;            // 1 = Stop timer, 0 = Start/Restart Timer
    Regs->TCR.bit.TRB = 1;            // 1 = reload timer
    Regs->TCR.bit.SOFT = 0;
    Regs->TCR.bit.FREE = 0;           // Timer Free Run Disabled
    Regs->TCR.bit.TIE = IntEnable;    // 0 = Disable/ 1 = Enable Timer Interrupt
}

//===========================================================================
// End of file.
//===========================================================================
