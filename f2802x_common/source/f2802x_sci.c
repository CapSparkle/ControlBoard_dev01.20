//###########################################################################
//
// FILE:    F2802x_Sci.c
//
// TITLE:    F2802x SCI Initialization & Support Functions.
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
// SCI_init:
//---------------------------------------------------------------------------
// This function initializes the SCI(s) to a known state.
//
void SCI_init(Uint16 BaudRate, Uint16 Parity, Uint16 Length, Uint16 StopBits)
{
    SciaRegs.SCICTL1.all = 0x0000;
    SciaRegs.SCICTL2.all = 0x0000;
    SciaRegs.SCICCR.all = (Length - 1) & 0x7;

    switch(Parity)
    {
        case 1: SciaRegs.SCICCR.bit.PARITYENA = 1; break;
        case 2: SciaRegs.SCICCR.bit.PARITYENA = 1; SciaRegs.SCICCR.bit.PARITY = 1; break;
    }
    SciaRegs.SCICCR.bit.STOPBITS = (StopBits == 2);

    SciaRegs.SCIHBAUD = (BaudRate >> 8) & 0xFF;
    SciaRegs.SCILBAUD = BaudRate & 0x00FF;
    SciaRegs.SCIPRI.all = 0x18;

    SciaRegs.SCIFFTX.all = 0x0;
    SciaRegs.SCIFFRX.all = 0x0;
    SciaRegs.SCIFFCT.all = 0x0;

    SciaRegs.SCICTL1.bit.SWRESET = 1;
    SciaRegs.SCIFFTX.bit.SCIRST = 1;
}

//---------------------------------------------------------------------------
// SCI_fifo_init:
//---------------------------------------------------------------------------
//
void SCI_fifo_init(Uint16 TxLevel, Uint16 RxLevel)
{
    SciaRegs.SCIFFTX.all = 0xE040 | TxLevel;
    SciaRegs.SCIFFRX.all = 0x2040 | RxLevel;
    SciaRegs.SCIFFCT.all = 0x0;
}

//---------------------------------------------------------------------------
// SCI_get:
//---------------------------------------------------------------------------
//
Uint16 SCI_get(void)
{
    while(!SciaRegs.SCIFFRX.bit.RXFFST)
    {
        if (SciaRegs.SCIRXST.bit.RXERROR || SciaRegs.SCIRXST.bit.BRKDT) {
            SciaRegs.SCICTL1.bit.SWRESET = 0;
            SciaRegs.SCICTL1.bit.SWRESET = 1;
        }
    }
    return SciaRegs.SCIRXBUF.all;
}

//---------------------------------------------------------------------------
// SCI_put:
//---------------------------------------------------------------------------
//
void SCI_put(Uint16 Data)
{
    while(!SciaRegs.SCICTL2.bit.TXRDY);
    SciaRegs.SCITXBUF = Data;
}

//---------------------------------------------------------------------------
// SCI_chars_avail:
//---------------------------------------------------------------------------
//
Uint16 SCI_chars_avail(void)
{
    if (SciaRegs.SCIRXST.bit.BRKDT) {
        SciaRegs.SCICTL1.bit.SWRESET = 0;
        SciaRegs.SCICTL1.bit.SWRESET = 1;
        return 0;
    }
    return SciaRegs.SCIFFRX.bit.RXFFST;
}

//---------------------------------------------------------------------------
// Example: InitSciGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as SCI pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution:
// Only one GPIO pin should be enabled for SCITXDA/B operation.
// Only one GPIO pin shoudl be enabled for SCIRXDA/B operation.
// Comment out other unwanted lines.

void InitSciGpio(void)
{
   InitSciaGpio();
}

void InitSciaGpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
/* Disable internal pull-up for the selected output pins
   to reduce power consumption. */
// Pull-ups can be enabled or disabled disabled by the user.

    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up for GPIO28 (SCIRXDA)
//    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;    // Enable pull-up for GPIO19 (SCIRXDA)
//    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;     // Enable pull-up for GPIO7  (SCIRXDA)

    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 1;       // Disable pull-up for GPIO29 (SCITXDA)
//    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 1;       // Disable pull-up for GPIO18 (SCITXDA)
//    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 1;       // Disable pull-up for GPIO12 (SCITXDA)

/* Set qualification for selected pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.
// This will select asynch (no qualification) for the selected pins.

    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (SCIRXDA)
//    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;  // Asynch input GPIO19 (SCIRXDA)
//    GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = 3;   // Asynch input GPIO7 (SCIRXDA)

/* Configure SCI-A pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SCI functional pins.

    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;   // Configure GPIO28 for SCIRXDA operation
//    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 2;   // Configure GPIO19 for SCIRXDA operation
//    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 2;    // Configure GPIO7  for SCIRXDA operation

    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;   // Configure GPIO29 for SCITXDA operation
//    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 2;   // Configure GPIO18 for SCITXDA operation
//    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 2;   // Configure GPIO12 for SCITXDA operation

    EDIS;
}

//===========================================================================
// End of file.
//===========================================================================
