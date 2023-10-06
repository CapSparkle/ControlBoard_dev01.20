
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "DSP28x_Project.h"
#include "IQmathLib.h"
#include "ApFilter3.h"
#include "interface.h"
#include "netcomm.h"

#define VERSION             120

#define CS_ADC              GpioDataRegs.GPADAT.bit.GPIO0
#define CS_SSI              GpioDataRegs.GPADAT.bit.GPIO1
#define ADC_RST             GpioDataRegs.GPADAT.bit.GPIO2
#define PODOGREV_INT        GpioDataRegs.GPADAT.bit.GPIO6
#define PODOGREV            GpioDataRegs.GPADAT.bit.GPIO12
#define HEAT_OUT            GpioDataRegs.GPADAT.bit.GPIO18
#define SCI_RESOUT          GpioDataRegs.GPADAT.bit.GPIO19
#define DSP_LED             GpioDataRegs.GPBDAT.bit.GPIO34

#define OHLAZHDENIE         GpioDataRegs.GPADAT.bit.GPIO3

#define TEMP_CPU            AdcResult.ADCRESULT1
#define TEMP_BF             AdcResult.ADCRESULT2

#endif // __CONFIG_H__


