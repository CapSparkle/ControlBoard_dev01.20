
#include "config.h"
#include "drv_at24x.h"
#include "adt75.h"
#include "ads1256.h"
#include "lir_da158a_02.h"
#include "params.h"

#define UPD_TIME        (Uint16)(1000 / UPD_FREQ)
#define HEATING_SIGNAL_PERIOD   100UL       //60000UL = 1 min

#define COOLING_STEP_PERIOD     250UL       //250 millisecs
#define COOLING_MACRO_PERIOD    100000UL    //100 sec

#define smoothTransition = 0;

Uint16 dev_number = 0;
Uint16 wr_flag = 0;
int16  spi_enable = 1;
int16  enc_enable = 1;
int16  temp_cpu = 0;
int16  temp_bf = 0;
int16  temp_on = 0;
int16  temp_off = 5;
int16  user_temp = TEMP_DEFAULT;
int32  lir_angle = 0;
Uint16 heating = 1;
Uint16 heating_int = 1;
Uint16 heating_mode = 0;
Uint16 heating_level = 0;
Uint32 heating_timer = 0;
Uint16 din_states = 0;
Uint16 upd_freq = 50;
int32  adc_tf = 0;


// === Cooling ===
int16  cool_on = 50;
int16  cool_off = 30;
Uint16 cooling = 1;
Uint16 cooling_mode = 1;
Uint16 cooling_level = 0;

Uint32 cooling_step_timer = 0;
Uint32 cooling_macro_timer = 0;

Uint32 dutyChangeStep = 0;
// ===============


int32 temp_bf_delta = 0; //_IQ16(1);

APFILTER3 temp1f;
APFILTER3 temp2f;

adc_value_t adc_values[ADC_NUM_CHANS];
APFILTER3 adc_f[ADC_NUM_CHANS];

int16 tsensX[TSENS_NUM_POINTS] = { 1043, 1429, 1816, 2176, 2551 };
int16 tsensY[TSENS_NUM_POINTS] = { -100, -50, 0, 50, 100 };

struct I2CMSG I2cMsg;

AT24X Eeprom;
ADT75 Tsens; //temperature sensor

static void ReadParams(void);
static void WriteParams(void);
static void LedBlink(Uint16 TimeMs);
static void TempTimer(Uint16 TimeMs);
static void TempControl(void);
static void AdcInterp(adc_value_t *v, int32 x, Uint16 numPts);
static void UpdateSensors(void);
static void AdcFiltrate(void);
extern void InitHeatGpio(void);

static void CoolingControl(void);
static void ChangeCoolingSignalDuty(bool increase);
static void CoolingUp(void);
static void CoolingDown(void);


void InterfaceInit(void)
{
    Uint16 i;

    memset(&temp1f,    0, sizeof(APFILTER3));
    memset(&temp2f,    0, sizeof(APFILTER3));
    memset(adc_values, 0, sizeof(adc_values));
    memset(adc_f,      0, sizeof(adc_f));
    memset(&I2cMsg,    0, sizeof(struct I2CMSG));

    memset(&Eeprom, 0, sizeof(AT24X));
    Eeprom.Msg        = &I2cMsg;
    Eeprom.Slave      = 0x50;
    Eeprom.RetryCount = 5;
    Eeprom.BusyTime   = 20;

    memset(&Tsens, 0, sizeof(ADT75));
    Tsens.Msg      = &I2cMsg;
    Tsens.Slave    = 0x48;
    Tsens.Temp     = TEMP_DEFAULT;

    ADS1256_Init();

    temp1f.dt = _IQ(1.0/UPD_FREQ);
    temp2f.dt = _IQ(1.0/UPD_FREQ);
    temp1f.Tf = _IQ(0.1);
    temp2f.Tf = _IQ(0.1);
    ApFilter3Init(&temp1f);
    ApFilter3Init(&temp2f);
    ApFilter3Reset(&temp1f, TEMP_DEFAULT);
    ApFilter3Reset(&temp2f, TEMP_DEFAULT);

    for(i = 0; i < ADC_NUM_CHANS; i++)
        adc_f[i].dt = _IQ(1.0/UPD_FREQ);

    ReadParams();

    if(smoothTransition){
        dutyChangeStep = COOLING_PULSE_NUMBER / 20;
    }
    else
    {
        dutyChangeStep = COOLING_PULSE_NUMBER;
    }


}

void InterfaceUpdate(void)
{
    static Uint16 i2c_index = 0;
    static Uint32 timer = 0;

    WriteParams();
    I2C_update(&I2cMsg);
    switch(i2c_index)
    {
        case 0: AT24X_Update(&Eeprom); if (!Eeprom.Func) i2c_index = 1; else break;
        case 1: ADT75_Update(&Tsens);  if (!Tsens.Busy)  i2c_index = 0; else break;
    }

    TempControl();
    if (spi_enable) ADS1256_Update();
    if (enc_enable) LIR_158A_02_Update();
    UpdateSensors();

    if (timerElapsed(timer) >= UPD_TIME)
    {
        I2C_Timer(&I2cMsg, UPD_TIME);
        AT24X_Timer(&Eeprom, UPD_TIME);
        LedBlink(UPD_TIME);
        TempTimer(UPD_TIME);
        AdcFiltrate();
        ApFilter3Calc(&temp1f);
        ApFilter3Calc(&temp2f);
        timer += UPD_TIME;
    }

    if((system_time - cooling_step_timer) >= COOLING_STEP_PERIOD)
    {
       cooling_step_timer += COOLING_STEP_PERIOD;
       cooling_macro_timer += COOLING_STEP_PERIOD;


       if(cooling_macro_timer >= COOLING_MACRO_PERIOD)
       {
           cooling_macro_timer -= COOLING_MACRO_PERIOD;
       }

       CoolingControl();
    }
}

Uint16 ReadReg(Uint16 index, Uint32 *data)
{
    param_t *param;

    if (index >= PARAM_COUNT) return 1;
    param = &params[index];

    if (param->flags & FLAG_SIZE) *data = *((Uint32 *)(param->var));
    else *data = *((Uint16 *)(param->var));
    if (param->flags & FLAG_INV) *data = -(*data);

    return 0;
}

Uint16 WriteReg(Uint16 index, Uint32 data)
{
    param_t *param;

    if (index >= PARAM_COUNT) return 1;
    param = &params[index];
    if (!(param->flags & FLAG_EDIT)) return 2;

    if (param->flags & FLAG_INV) data = -data;
    if (param->flags & FLAG_SIZE) *((Uint32 *)(param->var)) = data;
    else *((Uint16 *)(param->var)) = (Uint16)data;

    return 0;
}

static void ReadParams(void)
{
    param_t *param;
    Uint32 data;
    Uint16 i;

    DELAY_US(20000);
    I2C_reset();
    DELAY_US(10000);

    I2cMsg.BusyTimeout = 1000;

    AT24X_Read(&Eeprom, 0, (Uint16 *)&data, 1);
    if (AT24X_IsError(&Eeprom)) return;

    for(i = 0; i < PARAM_COUNT; i++)
    {
        param = &params[i];
        if (!(param->flags & FLAG_NVM)) continue;
        //read from eeprom
        if (!AT24X_Read(&Eeprom, i << 1, (Uint16 *)&data, 2)) break;
        if (data == -1UL) continue;
        // write to params variable
        WriteReg(i, data);
    }

    if (!netSlave || (netSlave > 255)) netSlave = 1;
    I2cMsg.BusyTimeout = 20;
}

static void WriteParams(void)
{
    if (!AT24X_IsReady(&Eeprom)) return;
    if (wr_flag) { AT24X_Func(&Eeprom, AT24X_WRITE, 1, 0, 0, PARAM_COUNT*2); wr_flag = 0; }
}

static void LedBlink(Uint16 TimeMs)
{
    static Uint16 LedTimer = 0;
    LedTimer += TimeMs;
    if (LedTimer >= 500)
    {
        DSP_LED = !DSP_LED;
        LedTimer -= 500;
    }
}

static Uint16 TempInput(void)
{
    Uint16 data;
    CS_SSI = 0;
    data = SPI_send(0);
    CS_SSI = 1;
    return (data != 0);
}

static void TempTimer(Uint16 TimeMs)
{
    heating_timer += TimeMs;
    if (heating_timer > HEATING_SIGNAL_PERIOD) heating_timer -= HEATING_SIGNAL_PERIOD;
}

static void TempControl(void)
{
#define CALC_BF_TEMP   1
#if CALC_BF_TEMP
    int16 temp1, temp2;
    int16 i, data, bf_flag = 0;
    int32 scale;
#endif
    int16 state;

    //temp1 = GetTemperatureC(TEMP_CPU);
    //temp1 = user_temp;
    temp1 = Tsens.Temp;

#if CALC_BF_TEMP
    data = TEMP_BF;
    //data = (int16)_IQ16mpy(data, temp_bf_gain);
    if (data < 100) bf_flag = 1;
    else if (data <= tsensX[0]) temp2 = tsensY[0];
    else if (data >= tsensX[TSENS_NUM_POINTS-1]) temp2 = tsensY[TSENS_NUM_POINTS-1];
    else
    {
        for(i = 1; i < TSENS_NUM_POINTS; i++)
            if (data <= tsensX[i]) break;
        scale = _IQ16div(tsensY[i] - tsensY[i-1], tsensX[i] - tsensX[i-1]);
        temp2 = tsensY[i-1] + (int16)_IQ16mpy(data - tsensX[i-1], scale);
    }
#else
    temp2 = TEMP_BF;
#endif

    if (netType <= 2) bf_flag = 1;

    temp1f.Input = _IQdiv(temp1, TEMP_MAX);
    temp2f.Input = _IQdiv(temp2, TEMP_MAX);

    temp_cpu = (int16)_IQrsmpy(temp1f.Output, TEMP_MAX);
    temp_bf  = !bf_flag ? (int16)_IQrsmpy(temp2f.Output, TEMP_MAX) : 9999;

    temp_bf = temp_bf + temp_bf_delta;

    if(temp_bf > TEMP_MAX){
        temp_bf = TEMP_MAX;
    }
    else {
        if(temp_bf < -100){
            temp_bf = -100;
        }
    }

    state = (netType != 3);
    if (spi_enable != state)
    {
        if (state) { CS_ADC = 1; CS_SSI = 1; InitSpiaGpio(); }
        else { InitHeatGpio(); CS_SSI = 0; }
        spi_enable = state;
    }
    enc_enable = (netType != 1) && (netType != 2) && spi_enable;

    switch(netType)
    {
        case 1:
        case 2:
            if (!heating) PODOGREV = 1;
            else PODOGREV = TempInput();
            break;
        case 3:
            if (!heating) PODOGREV = 1;
            else
            {
                if (temp_bf <= temp_on)  PODOGREV = 0;
                if (temp_bf >= temp_off) PODOGREV = 1;
            }
            HEAT_OUT = PODOGREV;
            break;
        default:
            if (!heating) PODOGREV = 1;
            else if (!heating_mode)
            {
                if (temp_bf <= temp_on)  PODOGREV = 0;
                if (temp_bf >= temp_off) PODOGREV = 1;
            }
            else
            {
                if (temp_bf >= 65) PODOGREV = 1;
                else if (heating_timer <= _IQmpy(_IQdiv(heating_level, 100), HEATING_SIGNAL_PERIOD)) PODOGREV = 0;
                else PODOGREV = 1;
            }
    }

    if (!heating_int) PODOGREV_INT = 1;
    else
    {
        if (temp_cpu <= 10) PODOGREV_INT = 0;
        if (temp_cpu >= 20) PODOGREV_INT = 1;
    }
}

static void ChangeCoolingSignalDuty(bool increase){

    if(increase)
    {
        if(COOLING_PULSE_DUTY_TERMINATOR < COOLING_PULSE_NUMBER)
        {
            COOLING_PULSE_DUTY_TERMINATOR += dutyChangeStep;

            if(COOLING_PULSE_DUTY_TERMINATOR > COOLING_PULSE_NUMBER)
            {
                COOLING_PULSE_DUTY_TERMINATOR = COOLING_PULSE_NUMBER;
            }
        }
    }
    else
    {
        if(COOLING_PULSE_DUTY_TERMINATOR > 0)
        {
            COOLING_PULSE_DUTY_TERMINATOR -= dutyChangeStep;

            if(COOLING_PULSE_DUTY_TERMINATOR > COOLING_PULSE_NUMBER)
            {
                COOLING_PULSE_DUTY_TERMINATOR = 0;
            }
        }
    }

    //COOLING_PULSE_DUTY_TERMINATOR = COOLING_PULSE_NUMBER / 2;
}

static void CoolingControl(void)
{
    if(PODOGREV == 0)
    {
        CoolingDown();
        return;
    }

    switch(netType)
    {
      case 1:
      case 2:
          if (!cooling)
          {
              CoolingDown();
          }
          //else OHLAZHDENIE = TempInput();
          break;
      case 3:
          if (!cooling)
          {
              CoolingDown();
          }
          else
          {
              if (temp_bf >= cool_on) {
                  CoolingUp();
              }
              if (temp_bf <= cool_off){
                  CoolingDown();
              }
          }
          //HEAT_OUT = OHLAZHDENIE;
          break;
      default:
        if (!cooling){
            CoolingDown();
        }
        else if (!cooling_mode)
        {
            if (temp_bf >= cool_on) {
                CoolingUp();
            }
            if (temp_bf <= cool_off){
                CoolingDown();
            }
        }
        else
        {
            if (temp_bf <= 26) {
                CoolingDown();
            }
            else if (cooling_macro_timer <= _IQmpy(_IQdiv(cooling_level + 5, 100), COOLING_MACRO_PERIOD)){
                CoolingUp();
            }
            else {
                CoolingDown();
            }
        }
    }
}

static void CoolingUp(){
    ChangeCoolingSignalDuty(true);
}

static void CoolingDown(){
    ChangeCoolingSignalDuty(false);
}

static void AdcInterp(adc_value_t *v, int32 x, Uint16 numPts)
{
    int32 dx, dy;
    Uint16 i;

    if (x <= v->x[0]) { v->value = v->y[0]; return; }
    if (x >= v->x[numPts-1]) { v->value = v->y[numPts-1]; return; }

    for(i = 1; i < numPts; i++)
        if (x <= v->x[i]) break;

    dx = v->x[i] - v->x[i-1];
    dy = v->y[i] - v->y[i-1];
    if (!dx || !dy) { v->value = v->y[i-1]; return; }

    if (_IQabs(dy) > _IQabs(dx))
        v->value = v->y[i-1] + _IQ30div(x - v->x[i-1], _IQ30div(dx, dy));
    else
        v->value = v->y[i-1] + _IQ30mpy(x - v->x[i-1], _IQ30div(dy, dx));

    v->out = _IQmpy(v->value, v->gain);
}

static void AdcFiltrate(void)
{
    APFILTER3 *fltr;
    Uint16 i;

    ads1256_data[3] = (int32)TEMP_BF << 12;

    for(i = 0; i < ADC_NUM_CHANS; i++)
    {
        fltr = &adc_f[i];
        if (fltr->Tf != adc_tf)
        {
            fltr->Tf = adc_tf;
            ApFilter3Init(fltr);
            ApFilter3Reset(fltr, 0);
        }
        fltr->Input = ads1256_data[i];
        ApFilter3Calc(fltr);
    }
}

static void UpdateSensors(void)
{
    Uint16 i, state = 0;
    int32 data;

    lir_angle = _IQ22div(360L * lir_position, 1L << lir_num_bits);

    switch(netType)
    {
    case 1:
        state = din_states;
        for(i = 0; i < ADC_NUM_CHANS; i++)
        {
            data = _IQabs(adc_f[i].Output);
            if (data >= _IQ24(DIN_ON_VALUE))  state |=  (1 << i);
            if (data <= _IQ24(DIN_OFF_VALUE)) state &= ~(1 << i);
        }
        din_states = state;
        break;
    case 2:
        for(i = 0; i < ADC_NUM_CHANS; i++)
            AdcInterp(&adc_values[i], adc_f[i].Output, 2);
        break;
    default:
        for(i = 0; i < 2; i++)
            AdcInterp(&adc_values[i], adc_f[i].Output, ADC_NUM_POINTS);
    }
}


