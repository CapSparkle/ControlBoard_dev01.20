
#ifndef __PARAMS_H__
#define __PARAMS_H__

#define PARAM_COUNT (sizeof(params) / sizeof(param_t))

#define FLAG_EDIT   0x0001
#define FLAG_NVM    0x0002
#define FLAG_SIZE   0x0004
#define FLAG_INV    0x0008

typedef const struct { void *var; Uint16 flags; } param_t;

param_t params[] =
{
/*000*/ (void *)&netType,               FLAG_EDIT|FLAG_NVM,
/*001*/ (void *)&netSlave,              FLAG_EDIT|FLAG_NVM,
/*002*/ (void *)&system_time,           FLAG_SIZE,
/*003*/ (void *)&temp_cpu,              0,
/*004*/ (void *)&temp_bf,               0,
/*005*/ (void *)&ads1256_data[0],       FLAG_SIZE,
/*006*/ (void *)&ads1256_data[1],       FLAG_SIZE,
/*007*/ (void *)&ads1256_data[2],       FLAG_SIZE,
/*008*/ (void *)&ads1256_data[3],       FLAG_SIZE,
/*009*/ (void *)&lir_num_bits,          FLAG_EDIT|FLAG_NVM,
/*010*/ (void *)&lir_position,          FLAG_SIZE,
/*011*/ (void *)&lir_angle,             FLAG_SIZE,
/*012*/ (void *)&adc_values[0].value,   FLAG_SIZE,
/*013*/ (void *)&adc_values[0].min,     FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*014*/ (void *)&adc_values[0].max,     FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*015*/ (void *)&adc_values[0].y[0],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*016*/ (void *)&adc_values[0].y[1],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*017*/ (void *)&adc_values[0].y[2],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*018*/ (void *)&adc_values[0].y[3],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*019*/ (void *)&adc_values[0].y[4],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*020*/ (void *)&adc_values[0].x[0],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*021*/ (void *)&adc_values[0].x[1],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*022*/ (void *)&adc_values[0].x[2],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*023*/ (void *)&adc_values[0].x[3],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*024*/ (void *)&adc_values[0].x[4],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*025*/ (void *)&heating_int,           FLAG_EDIT|FLAG_NVM,
/*026*/ (void *)&din_states,            0,
/*027*/ (void *)&upd_freq,              FLAG_EDIT|FLAG_NVM,
/*028*/ (void *)&adc_values[1].value,   FLAG_SIZE,
/*029*/ (void *)&adc_values[1].y[0],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*030*/ (void *)&adc_values[1].y[1],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*031*/ (void *)&adc_values[1].x[0],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*032*/ (void *)&adc_values[1].x[1],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*033*/ (void *)&adc_values[2].value,   FLAG_SIZE,
/*034*/ (void *)&adc_values[2].y[0],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*035*/ (void *)&adc_values[2].y[1],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*036*/ (void *)&adc_values[2].x[0],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*037*/ (void *)&adc_values[2].x[1],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*038*/ (void *)&adc_values[3].value,   FLAG_SIZE,
/*039*/ (void *)&adc_values[3].y[0],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*040*/ (void *)&adc_values[3].y[1],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*041*/ (void *)&adc_values[3].x[0],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*042*/ (void *)&adc_values[3].x[1],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*043*/ (void *)&adc_values[1].y[2],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*044*/ (void *)&adc_values[1].y[3],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*045*/ (void *)&adc_values[1].y[4],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*046*/ (void *)&adc_values[1].x[2],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*047*/ (void *)&adc_values[1].x[3],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*048*/ (void *)&adc_values[1].x[4],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*049*/ (void *)&lir_offset,            FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*050*/ (void *)&adc_tf,                FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*051*/ (void *)&adc_f[0].Output,       FLAG_SIZE,
/*052*/ (void *)&adc_f[1].Output,       FLAG_SIZE,
/*053*/ (void *)&heating,               FLAG_EDIT|FLAG_NVM,
/*054*/ (void *)&tsensX[0],             FLAG_EDIT|FLAG_NVM,
/*055*/ (void *)&tsensX[1],             FLAG_EDIT|FLAG_NVM,
/*056*/ (void *)&tsensX[2],             FLAG_EDIT|FLAG_NVM,
/*057*/ (void *)&tsensX[3],             FLAG_EDIT|FLAG_NVM,
/*058*/ (void *)&tsensX[4],             FLAG_EDIT|FLAG_NVM,
/*059*/ (void *)&AdcResult.ADCRESULT2,  0,
/*060*/ (void *)&dev_number,            FLAG_EDIT|FLAG_NVM,
/*061*/ (void *)&temp_on,               FLAG_EDIT|FLAG_NVM,
/*062*/ (void *)&temp_off,              FLAG_EDIT|FLAG_NVM,
/*063*/ (void *)&adc_f[2].Output,       FLAG_SIZE,
/*064*/ (void *)&adc_f[3].Output,       FLAG_SIZE,
/*065*/ (void *)&adc_values[0].y[5],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*066*/ (void *)&adc_values[0].y[6],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*067*/ (void *)&adc_values[0].y[7],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*068*/ (void *)&adc_values[0].y[8],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*069*/ (void *)&adc_values[0].y[9],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*070*/ (void *)&adc_values[0].y[10],   FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*071*/ (void *)&adc_values[0].y[11],   FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*072*/ (void *)&adc_values[0].y[12],   FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*073*/ (void *)&adc_values[0].y[13],   FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*074*/ (void *)&adc_values[0].y[14],   FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*075*/ (void *)&adc_values[0].x[5],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*076*/ (void *)&adc_values[0].x[6],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*077*/ (void *)&adc_values[0].x[7],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*078*/ (void *)&adc_values[0].x[8],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*079*/ (void *)&adc_values[0].x[9],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*080*/ (void *)&adc_values[0].x[10],   FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*081*/ (void *)&adc_values[0].x[11],   FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*082*/ (void *)&adc_values[0].x[12],   FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*083*/ (void *)&adc_values[0].x[13],   FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*084*/ (void *)&adc_values[0].x[14],   FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*085*/ (void *)&adc_values[1].y[5],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*086*/ (void *)&adc_values[1].y[6],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*087*/ (void *)&adc_values[1].y[7],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*088*/ (void *)&adc_values[1].y[8],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*089*/ (void *)&adc_values[1].y[9],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*090*/ (void *)&adc_values[1].y[10],   FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*091*/ (void *)&adc_values[1].y[11],   FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*092*/ (void *)&adc_values[1].y[12],   FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*093*/ (void *)&adc_values[1].y[13],   FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*094*/ (void *)&adc_values[1].y[14],   FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*095*/ (void *)&adc_values[1].x[5],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*096*/ (void *)&adc_values[1].x[6],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*097*/ (void *)&adc_values[1].x[7],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*098*/ (void *)&adc_values[1].x[8],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*099*/ (void *)&adc_values[1].x[9],    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*100*/ (void *)&adc_values[1].x[10],   FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*101*/ (void *)&adc_values[1].x[11],   FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*102*/ (void *)&adc_values[1].x[12],   FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*103*/ (void *)&adc_values[1].x[13],   FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*104*/ (void *)&adc_values[1].x[14],   FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*105*/ (void *)&adc_values[0].out,     FLAG_SIZE,
/*106*/ (void *)&adc_values[0].gain,    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*107*/ (void *)&adc_values[1].out,     FLAG_SIZE,
/*108*/ (void *)&adc_values[1].gain,    FLAG_EDIT|FLAG_NVM|FLAG_SIZE,
/*109*/ (void *)&heating_mode,          FLAG_EDIT|FLAG_NVM,
/*110*/ (void *)&heating_level,         FLAG_EDIT|FLAG_NVM,
/*111*/ (void *)&cool_on,               FLAG_EDIT|FLAG_NVM,
/*112*/ (void *)&cool_off,              FLAG_EDIT|FLAG_NVM,
/*113*/ (void *)&cooling,               FLAG_EDIT|FLAG_NVM,
/*114*/ (void *)&cooling_mode,          FLAG_EDIT|FLAG_NVM,
/*115*/ (void *)&cooling_level,         FLAG_EDIT|FLAG_NVM,
};

#define TSENS_NUM_POINTS    5
const int16 tsensY[] = { -100, -50, 0, 50, 100 };

#endif // __PARAMS_H__


