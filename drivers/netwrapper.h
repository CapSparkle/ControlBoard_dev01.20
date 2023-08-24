#ifndef NETWRAPPER_H
#define NETWRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

#define NET_BUF_LEN 256

struct NetBuf {
    int state;
    int len;
    int flag;
    unsigned short fcs;
    unsigned char data[NET_BUF_LEN];
    unsigned long timer;
};

void async_wrap(struct NetBuf *tx_buf, unsigned char *src, int len);
int async_unwrap_char(struct NetBuf *rx_buf, unsigned char byte);

#ifdef __cplusplus
}
#endif

#endif // NETWRAPPER_H
