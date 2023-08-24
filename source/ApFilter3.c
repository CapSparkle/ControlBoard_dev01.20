
#include "IQmathLib.h"
#include "ApFilter3.h"


void ApFilter3Init(APFILTER3 *p)
{
	p->K1 = _IQdiv(p->dt, (p->dt + p->Tf));
	p->K2 = _IQdiv(p->Tf, (p->dt + p->Tf));
}

void ApFilter3Config(APFILTER3 *p, long Cutoff, long Value)
{
    long Tf = !Cutoff ? 0 : _IQdiv(1, Cutoff /** 60L*/);
    if (p->Tf != Tf)
    {
        p->Tf = Tf;
        ApFilter3Init(p);
        ApFilter3Reset(p, Value);
    }
}

void ApFilter3Reset(APFILTER3 *p, long Value)
{
	p->Output = Value;
	p->PrevOut = Value;

	p->Output1 = Value;
	p->PrevOut1 = Value;

	p->Output2 = Value;
	p->PrevOut2 = Value;
}

void ApFilter3Calc(APFILTER3 *p)
{
    if (!p->Tf) { p->Output = p->Input; return; }

	p->Output1 = _IQmpy(p->Input,p->K1) + _IQmpy(p->PrevOut1,p->K2);
	p->PrevOut1 = p->Output1;

	p->Output2 = _IQmpy(p->Output1,p->K1) + _IQmpy(p->PrevOut2,p->K2);
	p->PrevOut2 = p->Output2;

	p->Output = _IQmpy(p->Output2,p->K1) + _IQmpy(p->PrevOut,p->K2);
	p->PrevOut = p->Output;
}


