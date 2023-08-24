
#ifndef __ADS1256_H__
#define __ADS1256_H__

extern int32 ads1256_data[];
extern Uint16 ads1256_status;
extern Uint16 ads1256_error;

void ADS1256_Init();
void ADS1256_Update();

#endif

