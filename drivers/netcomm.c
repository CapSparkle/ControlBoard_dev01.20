#include <string.h>
#include "DSP28x_Project.h"
#include "netcomm.h"
#include "netwrapper.h"
#include "netcrc.h"
#include "neterrors.h"

#define PARITY          0
#define STOP_BITS       1

#define RX_TIMEOUT      2
#define TX_TIMEOUT      2
#define TX_POST_DELAY   (Uint32)(1.0e6 * 10 / RS_SPEED)

#define SCI_RESOUT      GpioDataRegs.GPADAT.bit.GPIO19

Uint16 netSlave = 1;
Uint16 netType = 0;

extern Uint16 wr_flag;
extern int16  temp_cpu;
extern int16  temp_bf;

struct NetBuf rx_buf;
struct NetBuf tx_buf;

static void EnableRecieve(void);
extern Uint16 ReadReg(Uint16 index, Uint32 *data);
extern Uint16 WriteReg(Uint16 index, Uint32 data);
__interrupt void NetCommRxIsrHandler(void);
__interrupt void NetCommTxIsrHandler(void);


void NetCommInit(void)
{
    memset(&rx_buf, 0, sizeof(rx_buf));
    memset(&tx_buf, 0, sizeof(tx_buf));

    SCI_init(SCI_BRR(RS_SPEED), PARITY, 8, STOP_BITS);

    EALLOW;
    PieVectTable.SCIRXINTA = &NetCommRxIsrHandler;
    PieVectTable.SCITXINTA = &NetCommTxIsrHandler;
    EDIS;

    IER |= M_INT9;
    PieCtrlRegs.PIEIER9.bit.INTx1 = 1;  // SCIRXINTA
    PieCtrlRegs.PIEIER9.bit.INTx2 = 1;  // SCITXINTA

    SCI_rx_enable();
    SCI_rx_int_enable();
}

void NetCommUpdate(void)
{
    if (rx_buf.flag)
    {
        if (timerElapsed(rx_buf.timer) >= RX_TIMEOUT)
        {
            SCI_reset();
            rx_buf.state = 0;
            rx_buf.flag = 0;
        }
    }
    if (tx_buf.flag)
    {
        if (timerElapsed(tx_buf.timer) >= TX_TIMEOUT)
        {
            EnableRecieve();
            tx_buf.flag = 0;
        }
    }
    else if (SCI_RESOUT)
    {
        EnableRecieve();
    }
}

__interrupt void NetCommRxIsrHandler(void)
{
    static unsigned char buf[10];
    Uint16 addr;
    Uint32 data;
    int16 error, len;

    PieCtrlRegs.PIEACK.bit.ACK9 = 1;
    if (SCI_getstatus() & SCI_RXST_BRKDT) { SCI_reset(); return; }
    rx_buf.timer = millis();
    rx_buf.flag = 1;

    error = async_unwrap_char(&rx_buf, (unsigned char)SCI_recieve());
    if (error < 0) return;
    if (error > 0) { rx_buf.state = 0; rx_buf.flag = 0; return; }
    if (rx_buf.data[0] != netSlave) { rx_buf.state = 0; rx_buf.flag = 0; return; }
    rx_buf.flag = 0;

    SCI_rx_disable();
    SCI_rx_int_disable();

    addr = ((Uint16)rx_buf.data[3] << 8) | ((Uint16)rx_buf.data[2] & 0xFF);
    switch(rx_buf.data[1])
    {
    case 1:
        error = (int16)ReadReg(addr, &data);
        if (error) break;
        buf[4] = (data >> 0)  & 0xFF;
        buf[5] = (data >> 8)  & 0xFF;
        buf[6] = (data >> 16) & 0xFF;
        buf[7] = (data >> 24) & 0xFF;
        buf[8] = temp_cpu & 0xFF;
        buf[9] = temp_bf  & 0xFF;
        len = 10;
        break;
    case 2:
        data  = ((Uint32)rx_buf.data[7] << 24);
        data |= ((Uint32)rx_buf.data[6] << 16);
        data |= ((Uint32)rx_buf.data[5] << 8);
        data |= ((Uint32)rx_buf.data[4] << 0);
        error = (int16)WriteReg(addr, data);
        if (!error) { len = 4; if (addr == 1) wr_flag = 1; }
        break;
    default:
        error = -1;
    }

    memcpy(buf, rx_buf.data, 4);
    if (error) { buf[1] |= 0x80; len = 2; }
    async_wrap(&tx_buf, buf, len);
    tx_buf.state = 0;

    SCI_RESOUT = 1;
    SCI_tx_enable();
    SCI_tx_int_enable();
    SCI_transmit(tx_buf.data[0]);
    tx_buf.flag = 1;
    tx_buf.timer = millis();
}

__interrupt void NetCommTxIsrHandler(void)
{
    PieCtrlRegs.PIEACK.bit.ACK9 = 1;
    if (++tx_buf.state < tx_buf.len)
    {
        SCI_transmit(tx_buf.data[tx_buf.state]);
        tx_buf.timer = millis();
    }
    else
    {
        EnableRecieve();
        tx_buf.flag = 0;
    }
}

static void EnableRecieve(void)
{
    SCI_tx_disable();
    SCI_tx_int_disable();
    DELAY_US(TX_POST_DELAY);
    SCI_RESOUT = 0;
    SCI_rx_enable();
    SCI_rx_int_enable();
}


