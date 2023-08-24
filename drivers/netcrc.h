#ifndef NETCRC_H
#define NETCRC_H

#ifdef __cplusplus
extern "C" {
#endif

#define INIT_FCS    0xffff  /* Initial FCS value */
#define GOOD_FCS    0xf0b8  /* Good final FCS value */

unsigned short calc_fcs(unsigned short fcs, unsigned char c);
unsigned short calc_crc16(unsigned short fcs, unsigned char *buf, int len);

#ifdef __cplusplus
}
#endif

#endif // NETCRC_H
