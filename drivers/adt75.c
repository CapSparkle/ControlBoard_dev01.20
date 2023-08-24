
#include "DSP28x_Project.h"
#include "adt75.h"


void ADT75_Update(ADT75 *v)
{
    if (v->Busy)
    {
        if (v->Msg->Status == I2C_MSGSTAT_INACTIVE)
        {
            v->Temp = (int16)((v->Msg->Buffer[0] << 8) | v->Msg->Buffer[1]) >> 8;
            v->Busy = 0;
        }
        else if (v->Msg->Status == I2C_MSGSTAT_NACK)
        {
            v->Busy = 0;
            v->Errors++;
            v->Msg->Status = I2C_MSGSTAT_INACTIVE;
        }
    }
    else
    {
        v->Msg->Slave     = v->Slave;
        v->Msg->TxBytes   = 1;
        v->Msg->RxBytes   = 2;
        v->Msg->Buffer[0] = 0;
        v->Msg->Status    = I2C_MSGSTAT_SEND_NOSTOP;
        v->Busy           = 1;
    }
}

