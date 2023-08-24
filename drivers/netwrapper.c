#include "netwrapper.h"
#include "netcrc.h"
#include "neterrors.h"

#define BOF             0xc0 /* Beginning of frame */
#define XBOF            0xff
#undef  EOF
#define EOF             0xc1 /* End of frame */
#define CE              0x7d /* Control escape */
#define TRANS           0x20 /* Transparency modifier */

#define OUTSIDE_FRAME   0
#define BEGIN_FRAME     1
#define LINK_ESCAPE     2
#define INSIDE_FRAME    3


static inline void stuff_byte(struct NetBuf *tx_buf, unsigned char byte)
{
    switch(byte) {
    case BOF:
    case EOF:
    case CE:
        tx_buf->data[tx_buf->len++] = CE;
        tx_buf->data[tx_buf->len++] = byte ^ TRANS;
        break;
    default:
        tx_buf->data[tx_buf->len++] = byte;
    }
}

void async_wrap(struct NetBuf *tx_buf, unsigned char *src, int len)
{
    tx_buf->fcs = INIT_FCS;
    tx_buf->len = 0;
    tx_buf->data[tx_buf->len++] = BOF;
    while(len--) {
        stuff_byte(tx_buf, *src);
        tx_buf->fcs = calc_fcs(tx_buf->fcs, *src);
        src++;
    }
    tx_buf->fcs = ~tx_buf->fcs;
    stuff_byte(tx_buf, (unsigned char)(tx_buf->fcs & 0xFF));
    stuff_byte(tx_buf, (unsigned char)((tx_buf->fcs >> 8) & 0xFF));
    tx_buf->data[tx_buf->len++] = EOF;
}

static inline int async_unwrap_ce(struct NetBuf *rx_buf)
{
    switch(rx_buf->state) {
    case OUTSIDE_FRAME:
    case LINK_ESCAPE:
        return NET_ERR_FRAME;
    case BEGIN_FRAME:
    case INSIDE_FRAME:
    default:
        rx_buf->state = LINK_ESCAPE;
    }
    return NET_ERR_BUSY;
}

static inline int async_unwrap_bof(struct NetBuf *rx_buf)
{
    switch(rx_buf->state) {
    case LINK_ESCAPE:
    case INSIDE_FRAME:
        return NET_ERR_FRAME;
    case OUTSIDE_FRAME:
    case BEGIN_FRAME:
    default:
        break;
    }
    rx_buf->state = BEGIN_FRAME;
    rx_buf->len = 0;
    rx_buf->fcs = INIT_FCS;
    return NET_ERR_BUSY;
}

static inline int async_unwrap_eof(struct NetBuf *rx_buf)
{
    switch(rx_buf->state) {
    case OUTSIDE_FRAME:
        return NET_ERR_FRAME;
    case BEGIN_FRAME:
    case LINK_ESCAPE:
    case INSIDE_FRAME:
    default:
        rx_buf->state = OUTSIDE_FRAME;
        if (rx_buf->fcs != GOOD_FCS) return NET_ERR_CRC;
        return NET_ERR_SUCCESS;
    }
}

static inline int async_unwrap_other(struct NetBuf *rx_buf, unsigned char byte)
{
    switch(rx_buf->state) {
    case OUTSIDE_FRAME:
        if (byte != XBOF) return NET_ERR_FRAME;
        break;
    case LINK_ESCAPE:
        byte ^= TRANS;
    default:
        if (rx_buf->len < NET_BUF_LEN) {
            rx_buf->data[rx_buf->len++] = byte;
            rx_buf->fcs = calc_fcs(rx_buf->fcs, byte);
            rx_buf->state = INSIDE_FRAME;
        }
        else return NET_ERR_BUF_OVF;
    }
    return NET_ERR_BUSY;
}

int async_unwrap_char(struct NetBuf *rx_buf, unsigned char byte)
{
    switch(byte) {
        case CE:  return async_unwrap_ce(rx_buf);
        case BOF: return async_unwrap_bof(rx_buf);
        case EOF: return async_unwrap_eof(rx_buf);
        default:  return async_unwrap_other(rx_buf, byte);
    }
}

