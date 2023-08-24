
#ifndef __ADT75__
#define __ADT75__

typedef struct {
    struct I2CMSG *Msg;
    Uint16  Slave;
    int16   Temp;
    Uint16  Errors;
    Uint16  Busy;
} ADT75;

void ADT75_Update(ADT75 *v);

#endif /* __ADT75__ */





