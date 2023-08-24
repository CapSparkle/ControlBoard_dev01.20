#ifndef NETCOMM_H
#define NETCOMM_H

#ifdef __cplusplus
extern "C" {
#endif

extern Uint16 netSlave;
extern Uint16 netType;

void NetCommInit(void);
void NetCommUpdate(void);

#ifdef __cplusplus
}
#endif

#endif // NETCOMM_H
