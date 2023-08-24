//###########################################################################
//
// FILE:    F2802x_I2C.c
//
// TITLE:    F2802x I2C Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2802x Support Library v230 $
// $Release Date: Fri May  8 07:43:05 CDT 2015 $
// $Copyright: Copyright (C) 2008-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "F2802x_Device.h"     // Headerfile Include File
#include "f2802x_examples.h"   // Examples Include File

#define I2C_CLOCK_SPEED     9e6
#define I2C_IPSC_DIV        (Uint16)(SYSCLK / I2C_CLOCK_SPEED)

//#define I2C_D_VAL         7 // I2C_IPSC_DIV == 0
//#define I2C_D_VAL         6 // I2C_IPSC_DIV == 1
#define I2C_D_VAL           5 // I2C_IPSC_DIV > 1

#define I2C_STOP            0x0800
#define I2C_START           0x2000

Uint16 i2c_msg_counter = 0;
Uint16 i2c_al_counter = 0;
Uint16 i2c_nack_counter = 0;
Uint16 i2c_buserr_counter = 0;

static void ResetFifo();


void I2C_init(Uint32 Speed)
{
    I2caRegs.I2CMDR.all  = 0x00;
    I2caRegs.I2CPSC.all  = I2C_IPSC_DIV - 1;
    I2caRegs.I2CCLKL     = (I2C_CLOCK_SPEED/2) / Speed - I2C_D_VAL;
    I2caRegs.I2CCLKH     = I2caRegs.I2CCLKL;
    I2caRegs.I2CIER.all  = 0x00;
    I2caRegs.I2CFFTX.all = 0x6000;
    I2caRegs.I2CFFRX.all = 0x2040;
    I2caRegs.I2CMDR.all  = 0x20;
}

void I2C_msgSend(struct I2CMSG *Msg, Uint16 DeviceAddr, Uint16 Command, Uint16 NumByteToWrite, Uint16 NumByteToRead)
{
    Msg->Slave   = DeviceAddr;
    Msg->RxBytes = NumByteToRead;
    Msg->TxBytes = NumByteToWrite;
    Msg->Status  = Command;
}

void I2C_update(struct I2CMSG *Msg)
{
    Uint16 i;

    if (I2caRegs.I2CSTR.bit.ARBL)
    {
        I2C_reset();
        i2c_al_counter++;
        Msg->Status = I2C_MSGSTAT_NACK;
        return;
    }

    switch(Msg->Status)
    {
        case I2C_MSGSTAT_SEND_WITHSTOP:
            i2c_msg_counter++;
            ResetFifo();
            I2caRegs.I2CSAR = Msg->Slave;
            I2caRegs.I2CCNT = Msg->TxBytes;
            for (i = 0; i < Msg->TxBytes; i++)
                I2caRegs.I2CDXR = Msg->Buffer[i];
            I2caRegs.I2CMDR.all = (0x4620|I2C_START|I2C_STOP);
            Msg->BusyTimer = Msg->BusyTimeout;
            Msg->Status = I2C_MSGSTAT_WRITE_BUSY;
            break;

        case I2C_MSGSTAT_WRITE_BUSY:
            if (!Msg->BusyTimer) { I2C_reset(); Msg->Status = I2C_MSGSTAT_NACK; i2c_buserr_counter++; }
            else if (I2caRegs.I2CSTR.bit.NACK) { Msg->Status = I2C_MSGSTAT_NACK; i2c_nack_counter++; }
            else if (I2caRegs.I2CSTR.bit.SCD) Msg->Status = I2C_MSGSTAT_INACTIVE;
            break;

        case I2C_MSGSTAT_SEND_NOSTOP:
            i2c_msg_counter++;
            ResetFifo();
            I2caRegs.I2CSAR = Msg->Slave;
            I2caRegs.I2CCNT = Msg->TxBytes;
            for (i = 0; i < Msg->TxBytes; i++)
                I2caRegs.I2CDXR = Msg->Buffer[i];
            I2caRegs.I2CMDR.all = (0x4620|I2C_START);
            Msg->BusyTimer = Msg->BusyTimeout;
            Msg->Status = I2C_MSGSTAT_SEND_NOSTOP_BUSY;
            break;

        case I2C_MSGSTAT_SEND_NOSTOP_BUSY:
            if (!Msg->BusyTimer) { I2C_reset(); Msg->Status = I2C_MSGSTAT_NACK; i2c_buserr_counter++; }
            else if (I2caRegs.I2CSTR.bit.NACK) { Msg->Status = I2C_MSGSTAT_NACK; i2c_nack_counter++; }
            else if (I2caRegs.I2CSTR.bit.XSMT && I2caRegs.I2CSTR.bit.ARDY) Msg->Status = I2C_MSGSTAT_RESTART;
            else break;

        case I2C_MSGSTAT_RESTART:
            ResetFifo();
            I2caRegs.I2CSAR = Msg->Slave;
            I2caRegs.I2CCNT = Msg->RxBytes;
            I2caRegs.I2CMDR.all = (0x4420|I2C_START|I2C_STOP);
            Msg->BusyTimer = Msg->BusyTimeout;
            Msg->Status = I2C_MSGSTAT_READ_BUSY;
            break;

        case I2C_MSGSTAT_READ_BUSY:
            if (!Msg->BusyTimer) { I2C_reset(); Msg->Status = I2C_MSGSTAT_NACK; i2c_buserr_counter++; }
            else if (I2caRegs.I2CSTR.bit.NACK) { Msg->Status = I2C_MSGSTAT_NACK; i2c_nack_counter++; }
            else if (I2caRegs.I2CSTR.bit.SCD)
            {
                Msg->Status = I2C_MSGSTAT_INACTIVE;
                for (i = 0; i < Msg->RxBytes; i++)
                    Msg->Buffer[i] = I2caRegs.I2CDRR;
            }
            break;
    }
}

void I2C_Timer(struct I2CMSG *Msg, Uint16 Time)
{
    if (Msg->BusyTimer > Time) Msg->BusyTimer -= Time;
    else Msg->BusyTimer = 0;
}

void I2C_reset(void)
{
    EALLOW;
#if 0
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 0;
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 0;
    GpioDataRegs.GPADAT.bit.GPIO28  = 0;
    GpioDataRegs.GPADAT.bit.GPIO29  = 0;
    GpioDataRegs.GPADAT.bit.GPIO29  = 1;
    DELAY_US(10);
    GpioDataRegs.GPADAT.bit.GPIO28  = 1;
#else
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;
    GpioDataRegs.GPBDAT.bit.GPIO32  = 0;
    GpioDataRegs.GPBDAT.bit.GPIO33  = 0;
    GpioDataRegs.GPBDAT.bit.GPIO33  = 1;
    DELAY_US(10);
    GpioDataRegs.GPBDAT.bit.GPIO32  = 1;
#endif
    EDIS;
    DELAY_US(10);

    InitI2CGpio();

    I2caRegs.I2CMDR.all = (0x4620|I2C_STOP);
    DELAY_US(100);
    I2caRegs.I2CMDR.bit.IRS = 0;
    DELAY_US(100);
    I2caRegs.I2CMDR.bit.IRS = 1;
}

static void ResetFifo(void)
{
    I2caRegs.I2CSTR.bit.SCD  = 1;
    I2caRegs.I2CSTR.bit.NACK = 1;
    I2caRegs.I2CSTR.bit.XSMT = 1;
    I2caRegs.I2CSTR.bit.ARDY = 1;

    I2caRegs.I2CFFRX.bit.RXFFRST = 0;
    I2caRegs.I2CFFTX.bit.TXFFRST = 0;
    I2caRegs.I2CFFRX.bit.RXFFRST = 1;
    I2caRegs.I2CFFTX.bit.TXFFRST = 1;
}

//---------------------------------------------------------------------------
// Example: InitI2CGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as I2C pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution:
// Only one GPIO pin should be enabled for SDAA operation.
// Only one GPIO pin shoudl be enabled for SCLA operation.
// Comment out other unwanted lines.

void InitI2CGpio(void)
{

   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.


//    GpioCtrlRegs.GPADIR.bit.GPIO28 = 1;
//    GpioCtrlRegs.GPADIR.bit.GPIO29 = 1;

    GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;

//    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up for GPIO28 (SDAA)
//    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;       // Enable pull-up for GPIO29 (SCLA)

    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;    // Enable pull-up for GPIO32 (SDAA)
    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;       // Enable pull-up for GPIO33 (SCLA)

/* Set qualification for selected pins to asynch only */
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

//    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (SDAA)
//    GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 3;  // Asynch input GPIO29 (SCLA)

    GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3;  // Asynch input GPIO32 (SDAA)
    GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3;  // Asynch input GPIO33 (SCLA)

/* Configure I2C pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be I2C functional pins.
// Comment out other unwanted lines.

//    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 2;   // Configure GPIO28 for SDAA operation
//    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 2;   // Configure GPIO29 for SCLA operation

    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;   // Configure GPIO32 for SDAA operation
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;   // Configure GPIO33 for SCLA operation

    EDIS;
}

//===========================================================================
// End of file.
//===========================================================================
