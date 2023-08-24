//###########################################################################
//
// FILE:   F2802x_GlobalPrototypes.h
//
// TITLE:  Global prototypes for F2802x Examples
//
//###########################################################################
// $TI Release: F2802x Support Library v230 $
// $Release Date: Fri May  8 07:43:05 CDT 2015 $
// $Copyright: Copyright (C) 2008-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef F2802x_GLOBALPROTOTYPES_H
#define F2802x_GLOBALPROTOTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

// f2802x_cputimers.c
#define TIMER_PERIOD(Freq)  (Uint32)(SYSCLK / Freq - 1)

// f2802x_sci.c
#define SCI_BRR(Speed)      (Uint16)((SYSCLK/8) / Speed - 1)

#define SCI_RXST_RXWAKE     0x02
#define SCI_RXST_PE         0x04
#define SCI_RXST_OE         0x08
#define SCI_RXST_FE         0x10
#define SCI_RXST_BRKDT      0x20
#define SCI_RXST_RXRDY      0x40
#define SCI_RXST_RXERROR    0x80

#define SCI_recieve()           SciaRegs.SCIRXBUF.all
#define SCI_transmit(d)         SciaRegs.SCITXBUF = d
#define SCI_getstatus()         SciaRegs.SCIRXST.all
#define SCI_reset()             SciaRegs.SCICTL1.bit.SWRESET = 0; SciaRegs.SCICTL1.bit.SWRESET = 1
#define SCI_rx_enable()         SciaRegs.SCICTL1.bit.RXENA = 1
#define SCI_rx_disable()        SciaRegs.SCICTL1.bit.RXENA = 0
#define SCI_tx_enable()         SciaRegs.SCICTL1.bit.TXENA = 1
#define SCI_tx_disable()        SciaRegs.SCICTL1.bit.TXENA = 0
#define SCI_rx_int_enable()     SciaRegs.SCICTL2.bit.RXBKINTENA = 1
#define SCI_rx_int_disable()    SciaRegs.SCICTL2.bit.RXBKINTENA = 0
#define SCI_tx_int_enable()     SciaRegs.SCICTL2.bit.TXINTENA = 1
#define SCI_tx_int_disable()    SciaRegs.SCICTL2.bit.TXINTENA = 0

// f2802x_spi.c
#define SPI_SLAVE           0
#define SPI_MASTER          1

#define SPI_MODE0           0
#define SPI_MODE1           1
#define SPI_MODE2           2
#define SPI_MODE3           3

#define SPI_BRR(Speed)      (Uint16)(SYSCLK / Speed - 1)

// f2802x_i2c.c
#define I2C_SUCCESS                   0
#define I2C_ERR_INIT_FAILED           1
#define I2C_ERR_BUSY                  2
#define I2C_ERR_TX_DATA               3
#define I2C_ERR_RX_DATA               4

#define I2C_MSGSTAT_INACTIVE          0x00
#define I2C_MSGSTAT_SEND_WITHSTOP     0x10
#define I2C_MSGSTAT_WRITE_BUSY        0x11
#define I2C_MSGSTAT_WRITE_WAIT        0x12
#define I2C_MSGSTAT_SEND_NOSTOP       0x20
#define I2C_MSGSTAT_SEND_NOSTOP_BUSY  0x21
#define I2C_MSGSTAT_RESTART           0x22
#define I2C_MSGSTAT_READ_BUSY         0x23
#define I2C_MSGSTAT_NACK              0x30

struct I2CMSG {
    Uint16 Status;      // Message Command
    Uint16 Slave;       // Address of slave
    Uint16 RxBytes;     // Number of valid bytes
    Uint16 TxBytes;     // Number of valid bytes
    Uint16 BusyTimer;   // Busy timer for line control
    Uint16 BusyTimeout; // Busy timeout for line control
    Uint16 Buffer[16];  // Array holding message data
};

extern Uint32 system_time;
#define millis()            system_time
#define timerElapsed(timer) (system_time - (timer))
extern void SystemTickUpdate(void);

/*---- shared global function prototypes -----------------------------------*/
extern void InitHardware(void);
extern void InitAdc(void);
extern void InitAdcAio(void);
extern void AdcOffsetSelfCal(void);
extern void AdcChanSelect(Uint16 ch_no);
extern Uint16 AdcConversion (void);
extern void InitPeripherals(void);
extern void InitECap(void);
extern void InitECapGpio(void);
extern void InitECap1Gpio(void);
extern void InitEPwm(void);
extern void InitEPwmGpio(void);
extern void InitEPwm1Gpio(void);
extern void InitEPwm2Gpio(void);
extern void InitEPwm3Gpio(void);
#if DSP28_EPWM4
extern void InitEPwm4Gpio(void);
#endif // endif DSP28_EPWM4
extern void InitCompGpio(void);
extern void InitComp1Gpio(void);
#if DSP28_COMP2
extern void InitComp2Gpio(void);
#endif // endif DSP28_COMP2
extern void InitGpio(void);
extern void I2C_init(Uint32 Speed);
extern void I2C_msgSend(struct I2CMSG *Msg, Uint16 DeviceAddr, Uint16 Command, Uint16 NumByteToWrite, Uint16 NumByteToRead);
extern void I2C_update(struct I2CMSG *Msg);
extern void I2C_Timer(struct I2CMSG *Msg, Uint16 Time);
extern void I2C_reset(void);
extern void InitI2CGpio(void);
extern void InitPieCtrl(void);
extern void InitPieVectTable(void);
extern void SCI_init(Uint16 BaudRate, Uint16 Parity, Uint16 Length, Uint16 StopBits);
extern void SCI_fifo_init(Uint16 TxLevel, Uint16 RxLevel);
extern Uint16 SCI_get(void);
extern void SCI_put(Uint16 Data);
extern Uint16 SCI_chars_avail(void);
extern void InitSciGpio(void);
extern void InitSciaGpio(void);
extern void SPI_init(Uint16 Master, Uint16 Mode, Uint16 BaudRate, Uint16 Length);
extern Uint16 SPI_send(Uint16 Data);
extern void SPI_transmit(Uint16 Data);
extern Uint16 SPI_recieve(void);
extern Uint16 SPI_ready(void);
extern void InitSpiGpio(void);
extern void InitSpiaGpio(void);
extern void InitSysCtrl(void);
extern void InitTzGpio(void);
extern void InitXIntrupt(void);
extern void InitPll(Uint16 pllcr, Uint16 clkindiv);
extern void InitPeripheralClocks(void);
extern void EnableInterrupts(void);
extern void DSP28x_usDelay(Uint32 Count);
#define KickDog ServiceDog     // For compatiblity with previous versions
extern void ServiceDog(void);
extern void DisableDog(void);
extern Uint16 CsmUnlock(void);
extern void IntOsc1Sel (void);
extern void IntOsc2Sel (void);
extern void XtalOscSel (void);
extern void ExtClkSel (void);
extern int16 GetTemperatureC(int16 sensorSample); // returns temp in deg. C
extern int16 GetTemperatureK(int16 sensorSample); // returns temp in deg. K
extern void Osc1Comp(int16 sensorSample);
extern void Osc2Comp(int16 sensorSample);

// DSP28_DBGIER.asm
extern void SetDBGIER(Uint16 dbgier);

//                 CAUTION
// This function MUST be executed out of RAM. Executing it
// out of OTP/Flash will yield unpredictable results
extern void InitFlash(void);

//---------------------------------------------------------------------------
// External symbols created by the linker cmd file
// DSP28 examples will use these to relocate code from one LOAD location
// in Flash to a different RUN location in internal RAM

extern uint16_t RamfuncsLoadStart;
extern uint16_t RamfuncsLoadSize;
extern uint16_t RamfuncsRunStart;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of F2802x_GLOBALPROTOTYPES_H

//===========================================================================
// End of file.
//===========================================================================
