
#include "config.h"


#define SYS_PERIOD_MS (Uint32)(SYSCLK / 1000)
Uint32 system_time = 0; //millisecs

static void InitUserGpio(void);
static void InitUserAdc(void);


void InitHardware(void)
{
    #if defined(FLASH_PROJ)
    // Copy time critical code and Flash setup code to RAM
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
    #endif

    // Initialize System Control
    InitSysCtrl();

    // Disable global Interrupts and higher priority real-time debug events
    DINT;
    DRTM;

    #if defined(FLASH_PROJ)
    // Call Flash Initialization to setup flash waitstates
    InitFlash();
    #endif

    // Initialize GPIO
    InitGpio();
    InitUserGpio();
    InitSpiaGpio();
    InitSciaGpio();
    InitI2CGpio();

    // Initialize the PIE control registers to their default state
    InitPieCtrl();

    // Disable CPU interrupts and clear all CPU interrupt flags
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR)
    InitPieVectTable();

    // Initialize all the Device Peripherals
    InitUserAdc();
    I2C_init(200000);
    ConfigCpuTimer(&CpuTimer0Regs, 0xFFFFFFFF, 0);
    ConfigCpuTimer(&CpuTimer1Regs, 0x0000FFFF, 0);

	// Start timers
	StartCpuTimer0();
	StartCpuTimer1();
}

static void InitUserGpio(void)
{
	EALLOW;

    GpioCtrlRegs.GPADIR.bit.GPIO0  = 1;   // CS_ADC
    GpioDataRegs.GPADAT.bit.GPIO0  = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO1  = 1;   // CS_SSI
    GpioDataRegs.GPADAT.bit.GPIO1  = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO2  = 1;   // ADC_RST
    GpioDataRegs.GPADAT.bit.GPIO2  = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO6  = 1;   // PODOGREV_INT
    GpioDataRegs.GPADAT.bit.GPIO6  = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;   // PODOGREV
    GpioDataRegs.GPADAT.bit.GPIO12 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO19 = 1;   // SCI_RESOUT
    GpioDataRegs.GPADAT.bit.GPIO19 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;   // DSP_LED
    GpioDataRegs.GPBDAT.bit.GPIO34 = 0;

    // OHLAZHDENIE
    // EPWM
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;
    //GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE; // Phase loading disabled
    EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = 7;
    EPwm3Regs.TBCTL.bit.CLKDIV = 7;
    //TBCLK = SYSCLK / (HSPCLKDIV * CLKDIV) = 50223 (which is roughlt 50 KHz)
    //...if assuming we have 90'000'000 Hz SYSCLK

    EPwm3Regs.TBPRD = 50; //50223 / 1000 = 50;

    EPwm3Regs.CMPA.half.CMPA = EPwm3Regs.TBPRD / 2;

    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm3Regs.AQCTLA.bit.PRD = AQ_SET;

	EDIS;
}

static void InitUserAdc(void)
{
    AdcRegs.ADCCTL1.bit.RESET = 1;
    asm(" RPT #14 || NOP");

    InitAdc();
    AdcOffsetSelfCal();
    AdcChanSelect(0);

    EALLOW;

    AdcRegs.ADCCTL1.bit.TEMPCONV    = 1;
    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcRegs.ADCSOC0CTL.bit.CHSEL    = 5;
    AdcRegs.ADCSOC0CTL.bit.TRIGSEL  = 2;
    AdcRegs.ADCSOC0CTL.bit.ACQPS    = 36;
    AdcRegs.ADCSOC1CTL.bit.CHSEL    = 5;
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL  = 2;
    AdcRegs.ADCSOC1CTL.bit.ACQPS    = 36;
    AdcRegs.ADCSOC2CTL.bit.CHSEL    = 0;
    AdcRegs.ADCSOC2CTL.bit.TRIGSEL  = 2;
    AdcRegs.ADCSOC2CTL.bit.ACQPS    = 36;

    EDIS;
}

void InitHeatGpio(void)
{
    EALLOW;
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO17  = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO18  = 1;
    GpioDataRegs.GPADAT.bit.GPIO18  = 1;
    EDIS;
}

void SystemTickUpdate(void)
{
    static Uint32 lastTime = -1UL;
    Uint32 delta = lastTime - ReadCpuTimer0Counter();
    if (delta >= SYS_PERIOD_MS)
    {
        delta = _IQ1div(delta, SYS_PERIOD_MS) >> 1;
        system_time += delta;
        lastTime -= delta * SYS_PERIOD_MS;
    }
}

