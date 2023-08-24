
#ifndef __DRV_AT24X__
#define __DRV_AT24X__

#define AT24X_SUCCESS		 0
#define AT24X_BUSY			 1
#define AT24X_EDISCON		-1
#define AT24X_EWRITE_ERR	-2

#define AT24X_NONE		 	 0x00
#define AT24X_WRITE		 	 0x01
#define AT24X_READ			 0x02
#define AT24X_STATUS	 	 0x04
#define AT24X_WRITE_CODE	 0x10

typedef struct {
	struct I2CMSG *Msg;
	Uint16  Slave;
	Uint16  Func;
    Uint16  Mode;
    Uint16  Addr;
    Uint16 *Buffer;
    Uint16  Count;
    Uint16  RdData;
    Uint16  WrData;
    Uint16  TmpData;
	int16	Status;
	Uint16	RetryCount;
	Uint16  RetryCounter;
	Uint16	BusyTime;
	Uint16	BusyTimer;
	Uint16	DataIndex;
} AT24X;

#define AT24X_IsReady(pMem)	(!(pMem)->Func)
#define AT24X_IsError(pMem)	((pMem)->Status < 0)

void   AT24X_Update(AT24X *);
void   AT24X_Timer(AT24X *, Uint16 Time);
void   AT24X_Func(AT24X *, Uint16 Func, Uint16 Mode, Uint16 Addr, Uint16 *Data, Uint16 Count);
Uint16 AT24X_Read(AT24X *, Uint16 Addr, Uint16 *Data, Uint16 Count);

#endif /* __DRV_AT24X__*/

