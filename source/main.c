
#include "config.h"


void main(void)
{
	InitHardware();
	InterfaceInit();
	NetCommInit();
	EnableInterrupts();
	
	while(1)
	{
	    SystemTickUpdate();
	    NetCommUpdate();
	    InterfaceUpdate();
	}
}
