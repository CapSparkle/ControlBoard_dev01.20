//###########################################################################
//
// FILE:   F2802x_Spi.c
//
// TITLE:  F2802x SPI Initialization & Support Functions.
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
// InitSPI:
//---------------------------------------------------------------------------
// This function initializes the SPI(s) to a known state.
//
void SPI_init(Uint16 Master, Uint16 Mode, Uint16 BaudRate, Uint16 Length)
{
    SpiaRegs.SPICCR.bit.SPISWRESET = 0;
    SpiaRegs.SPICCR.all = (Length - 1) & 0xF;
    SpiaRegs.SPICTL.all = 0x0;
    SpiaRegs.SPICTL.bit.MASTER_SLAVE = Master;
    SpiaRegs.SPICTL.bit.TALK = Master;

    switch(Mode)
    {
        case 0: SpiaRegs.SPICTL.bit.CLK_PHASE = 1; break;
        case 2: SpiaRegs.SPICTL.bit.CLK_PHASE = 1; SpiaRegs.SPICCR.bit.CLKPOLARITY = 1; break;
        case 3: SpiaRegs.SPICCR.bit.CLKPOLARITY = 1; break;
    }

    SpiaRegs.SPIBRR = BaudRate;
    SpiaRegs.SPIPRI.all = 0x0030;

    SpiaRegs.SPICCR.bit.SPISWRESET = 1;
}

//---------------------------------------------------------------------------
// SPI_send:
//---------------------------------------------------------------------------
//
Uint16 SPI_send(Uint16 Data)
{
    SpiaRegs.SPITXBUF = Data << (0xF - (SpiaRegs.SPICCR.all & 0xF));
    while (!SpiaRegs.SPISTS.bit.INT_FLAG);
    return (SpiaRegs.SPIRXBUF);
}

//---------------------------------------------------------------------------
// SPI_transmit:
//---------------------------------------------------------------------------
//
void SPI_transmit(Uint16 Data)
{
    SpiaRegs.SPITXBUF = Data << (0xF - (SpiaRegs.SPICCR.all & 0xF));
}

//---------------------------------------------------------------------------
// SPI_recieve:
//---------------------------------------------------------------------------
//
Uint16 SPI_recieve(void)
{
    return SpiaRegs.SPIRXBUF;
}

//---------------------------------------------------------------------------
// SPI_ready:
//---------------------------------------------------------------------------
//
Uint16 SPI_ready(void)
{
    return SpiaRegs.SPISTS.bit.INT_FLAG;
}


//---------------------------------------------------------------------------
// Example: InitSpiGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as SPI pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution:
// For each SPI peripheral
// Only one GPIO pin should be enabled for SPISOMO operation.
// Only one GPIO pin should be enabled for SPISOMI operation.
// Only one GPIO pin should be enabled for SPICLKA operation.
// Only one GPIO pin should be enabled for SPISTEA operation.
// Comment out other unwanted lines.

void InitSpiGpio(void)
{
   InitSpiaGpio();
}

void InitSpiaGpio(void)
{

   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   // Enable pull-up on GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   // Enable pull-up on GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;   // Enable pull-up on GPIO18 (SPICLKA)
//    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;   // Enable pull-up on GPIO19 (SPISTEA)

/* Set qualification for selected pins to asynch only */
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // Asynch input GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch input GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Asynch input GPIO18 (SPICLKA)
//    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // Asynch input GPIO19 (SPISTEA)

/* Configure SPI-A pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SPI functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1; // Configure GPIO16 as SPISIMOA
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1; // Configure GPIO17 as SPISOMIA
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1; // Configure GPIO18 as SPICLKA
//    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1; // Configure GPIO19 as SPISTEA

    EDIS;
}

//===========================================================================
// End of file.
//===========================================================================
