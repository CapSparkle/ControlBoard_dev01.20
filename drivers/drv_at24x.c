
#include "DSP28x_Project.h"
#include "drv_at24x.h"

#define AT24X_READ_BUSY		0x20
#define AT24X_WRITE_BUSY	0x40

extern Uint16 ReadReg(Uint16 index, Uint32 *data);
extern Uint16 WriteReg(Uint16 index, Uint32 data);


void AT24X_Update(AT24X *v)
{
    Uint32 ulTemp;

	if (!v->Func) return;

	if (v->Func & AT24X_READ_BUSY)
	{
		if (v->Msg->Status == I2C_MSGSTAT_INACTIVE)
		{
			v->Func &= ~AT24X_READ_BUSY;
			v->RdData = (v->Msg->Buffer[0] << 8) | v->Msg->Buffer[1];
			if (!(v->Func & AT24X_WRITE))
			{
			    if (!v->Mode)
			    {
			        if (!v->Buffer) v->Count = 0;
			        else *v->Buffer = v->RdData;
			    }
			    else
			    {
	                if (!v->DataIndex) { v->TmpData = v->RdData; v->DataIndex = 1; }
	                else { WriteReg(v->Addr >> 2, ((Uint32)v->RdData << 16) | v->TmpData); v->DataIndex = 0; }
			    }
			}
			else if (v->RdData != v->WrData)
			{ 
				if (++v->RetryCounter < v->RetryCount)
				{
				    v->DataIndex = 0;
					v->Func &= ~AT24X_READ;
					return;
				}
				v->Status = AT24X_EWRITE_ERR;
				v->Func = 0;
				return;
			}
			else
			{
				v->RetryCounter = 0;
				v->Func &= ~AT24X_READ;
			}
			if (v->Count > 2) { v->Addr += 2; v->Count -= 2; if (!v->Mode && v->Buffer) v->Buffer++; }
			else { v->Status = AT24X_SUCCESS; v->Func = 0; v->Count = 0; }
		}
		else if (v->Msg->Status == I2C_MSGSTAT_NACK)
		{
			if ((v->Func & AT24X_WRITE) && (++v->RetryCounter < v->RetryCount))
			{
				v->Func &= ~(AT24X_READ|AT24X_READ_BUSY);
				return;
			}
			v->Status = AT24X_EDISCON;
			v->Func = 0;
			v->Msg->Status = I2C_MSGSTAT_INACTIVE;
		}
	}
	else if (v->Func & AT24X_WRITE_BUSY)
	{
		if (v->Msg->Status == I2C_MSGSTAT_INACTIVE)
		{
			v->Msg->Status = I2C_MSGSTAT_WRITE_WAIT;
			v->BusyTimer = v->BusyTime;
		}
		else if (v->Msg->Status == I2C_MSGSTAT_NACK)
		{
			if (++v->RetryCounter < v->RetryCount)
			{
			    v->DataIndex = 0;
				v->Func &= ~AT24X_WRITE_BUSY;
				return;
			}
			v->Status = AT24X_EDISCON;
			v->Func = 0;
			v->Msg->Status = I2C_MSGSTAT_INACTIVE;
		}
		else if ((v->Msg->Status == I2C_MSGSTAT_WRITE_WAIT) && !v->BusyTimer)
		{
		    v->RetryCounter = 0;
			v->Func &= ~AT24X_WRITE_BUSY;
			v->Msg->Status = I2C_MSGSTAT_INACTIVE;
		}
	}
	else if (v->Func & AT24X_READ)
	{
		v->Msg->Slave     = v->Slave;
		v->Msg->TxBytes   = 2;
		v->Msg->RxBytes   = 2;
		v->Msg->Buffer[0] = v->Addr >> 8;
		v->Msg->Buffer[1] = v->Addr & 0xFF;
		v->Msg->Status    = I2C_MSGSTAT_SEND_NOSTOP;
		v->Func          |= AT24X_READ_BUSY;
	}
	else if (v->Func & AT24X_WRITE)
	{
		v->Msg->Slave     = v->Slave;
		v->Msg->TxBytes   = 3;
		v->Msg->RxBytes   = 0;
		v->Msg->Buffer[0] = (v->Addr + (v->DataIndex & 0x1)) >> 8;
		v->Msg->Buffer[1] = (v->Addr + (v->DataIndex & 0x1)) & 0xFF;
		v->Msg->Status    = I2C_MSGSTAT_SEND_WITHSTOP;
		if (!(v->DataIndex & 0x1))
		{
		    if (!v->Mode)
		    {
	            if (!v->Buffer) v->WrData = 0;
	            else v->WrData = *v->Buffer;
		    }
		    else
		    {
                if (ReadReg(v->Addr >> 2, &ulTemp)) ulTemp = 0;
                if (!(v->DataIndex & 0x2)) v->WrData = (Uint16)ulTemp;
                else v->WrData = (Uint16)(ulTemp >> 16);
		    }
		    v->Msg->Buffer[2] = v->WrData >> 8;
		}
		else
		{
            v->Msg->Buffer[2] = v->WrData & 0xFF;
            v->Func |= AT24X_READ;
		}
		if (++v->DataIndex > 3) v->DataIndex = 0;
		v->Func |= AT24X_WRITE_BUSY;
	}
}

void AT24X_Timer(AT24X *v, Uint16 Time)
{
    if (v->BusyTimer > Time) v->BusyTimer -= Time;
    else v->BusyTimer = 0;
}

void AT24X_Func(AT24X *v, Uint16 Func, Uint16 Mode, Uint16 Addr, Uint16 *Data, Uint16 Count)
{
	if ((v->Status < 0) || !Count) return;
	v->Addr         = Addr << 1;
	v->Buffer       = Data;
	v->Count        = Count << 1;
	v->Mode         = Mode;
	v->Func         = Func;
	v->RetryCounter = 0;
	v->DataIndex    = 0;
	v->Status       = AT24X_BUSY;
}

Uint16 AT24X_Read(AT24X *v, Uint16 Addr, Uint16 *Data, Uint16 Count)
{
	Uint16 i, *Buf;
	Uint16 RetryCount = 0;

	Addr = Addr << 1;

	v->Msg->Slave     = v->Slave;
	v->Msg->TxBytes   = 2;
	v->Msg->RxBytes   = Count << 1;
    v->Msg->Buffer[0] = Addr >> 8;
    v->Msg->Buffer[1] = Addr & 0xFF;
    v->Msg->Status    = I2C_MSGSTAT_SEND_NOSTOP;

	while(v->Msg->Status != I2C_MSGSTAT_INACTIVE)
	{
	    I2C_Timer(v->Msg, 1);
		I2C_update(v->Msg);
		if (v->Msg->Status == I2C_MSGSTAT_NACK)
		{
		    if (++RetryCount < v->RetryCount)
		        v->Msg->Status = I2C_MSGSTAT_SEND_NOSTOP;
		    else
		    {
		        v->Status = AT24X_EDISCON;
		        v->Msg->Status = I2C_MSGSTAT_INACTIVE;
		        return 0;
		    }
		}
	}

	Buf = v->Msg->Buffer;
	for (i = 0; i < Count; i++)
	{
	    Data[i] = (Buf[0] << 8) | (Buf[1] & 0xFF);
	    Buf += 2;
	}

	return 1;
}



