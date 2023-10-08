
#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#define TEMP_DEFAULT    30
#define TEMP_HYST       3
#define TEMP_MAX        100

#define DIN_ON_VALUE    0.4
#define DIN_OFF_VALUE   0.2

#define ADC_NUM_CHANS   4
#define ADC_NUM_POINTS  15

typedef struct { int32 value, out, min, max, gain, x[ADC_NUM_POINTS], y[ADC_NUM_POINTS]; } adc_value_t;

extern Uint32 system_time;
extern Uint16 dev_number;
extern int16  temp_cpu;
extern int16  temp_bf;
extern int16  temp_on;
extern int16  temp_off;
extern int32  lir_angle;
extern Uint16 heating;
extern Uint16 heating_int;
extern Uint16 heating_mode;
extern Uint16 heating_level;
extern Uint16 din_states;
extern Uint16 upd_freq;
extern int32  adc_tf;
extern Uint32 system_time;
extern adc_value_t adc_values[ADC_NUM_CHANS];
extern APFILTER3 adc_f[ADC_NUM_CHANS];
extern int16 tsensX[];
extern int16 tsensY[];

extern int16  cool_on;
extern int16  cool_off;
extern Uint16 cooling;
extern Uint16 cooling_mode;
extern Uint16 cooling_level;

extern int32 temp_bf_delta;

extern Uint32 cooling_step_timer;
extern Uint32 cooling_macro_timer;

extern Uint32 dutyChangeStep;

extern bool compute_macro_periods;
extern bool smoothTransition;

void InterfaceInit(void);
void InterfaceUpdate(void);

#endif // __INTERFACE_H__



