
#include "DSP28x_Project.h"
#include "ads1256.h"
#include <string.h>

// General defines
#define ADC_COUNT           1
#define ADC_CH_COUNT        3
#define ADC_SELFCAL_EN      1
#define ADC_MASK            ((1U << ADC_COUNT) - 1)

#define SPI_FREQ            1000000
#define SPI_MODE            SPI_MODE1

// ADS1256 registers
#define REG_STATUS          0x00
#define REG_MUX             0x01
#define REG_ADCON           0x02
#define REG_DRATE           0x03
#define REG_IO              0x04
#define REG_OFC0            0x05
#define REG_OFC1            0x06
#define REG_OFC2            0x07
#define REG_FSC0            0x08
#define REG_FSC1            0x09
#define REG_FSC2            0x0A

// ADS1256 STATUS register bits
#define STATUS_DRDY         0x01
#define STATUS_BUFEN        0x02
#define STATUS_ACAL         0x04
#define STATUS_ORDER        0x08
#define STATUS_ID0          0x10
#define STATUS_ID1          0x20
#define STATUS_ID2          0x40
#define STATUS_ID3          0x80

// ADS1256 MUX register bits
#define MUX_NSEL(A)         ((A) & 0x0F)
#define MUX_PSEL(A)         (((A) & 0x0F) << 4)

// ADS1256 ADCON register bits
#define ADCON_PGA1          0x00
#define ADCON_PGA2          0x01
#define ADCON_PGA4          0x02
#define ADCON_PGA8          0x03
#define ADCON_PGA16         0x04
#define ADCON_PGA32         0x05
#define ADCON_PGA64         0x06
#define ADCON_SDCS_OFF      0x00
#define ADCON_SDCS_0_5uA    0x08
#define ADCON_SDCS_2uA      0x10
#define ADCON_SDCS_10uA     0x18
#define ADCON_CLKO_OFF      0x00
#define ADCON_CLKO_1        0x20
#define ADCON_CLKO_2        0x40
#define ADCON_CLKO_4        0x60

// ADS1256 DR register bits
#define DR_2_5SPS           0x03
#define DR_5SPS             0x13
#define DR_10SPS            0x23
#define DR_15SPS            0x33
#define DR_25SPS            0x43
#define DR_30SPS            0x53
#define DR_50SPS            0x63
#define DR_60SPS            0x72
#define DR_100SPS           0x82
#define DR_500SPS           0x92
#define DR_1000SPS          0xA1
#define DR_2000SPS          0xB0
#define DR_3750SPS          0xC0
#define DR_7500SPS          0xD0
#define DR_15000SPS         0xE0
#define DR_30000SPS         0xF0

// ADS1256 Command
#define CMD_WAKEUP          0x00
#define CMD_RDATA           0x01
#define CMD_RDATAC          0x03
#define CMD_SDATAC          0x0F
#define CMD_RREG            0x10
#define CMD_WREG            0x50
#define CMD_SELFCAL         0xF0
#define CMD_SELFOCAL        0xF1
#define CMD_SELFGCAL        0xF2
#define CMD_SYSOCAL         0xF3
#define CMD_SYSGCAL         0xF4
#define CMD_SYNC            0xFC
#define CMD_STANDBY         0xFD
#define CMD_RESET           0xFE

// ADS1256 Timings
#define RESET_DELAY1        10
#define RESET_DELAY2        500
#define READ_DELAY          7
#define CS_HIGH_DELAY       4
#define DRDY_BUSY_DELAY1    10
#define DRDY_BUSY_DELAY2    50000

// ADS1256 macro
#define ADC_RESET()         GpioDataRegs.GPADAT.bit.GPIO2 = 1; DELAY_US(RESET_DELAY1); GpioDataRegs.GPADAT.bit.GPIO2 = 0; DELAY_US(RESET_DELAY2)
#define SELECT_SPI(I)       GpioDataRegs.GPADAT.bit.GPIO0 = 0
#define DESELECT_SPI(I)     GpioDataRegs.GPADAT.bit.GPIO0 = 1

int32 ads1256_data[10];
Uint16 ads1256_chan[ADC_COUNT];
Uint16 ads1256_num = 0;
Uint16 ads1256_status = 0;
Uint16 ads1256_error = 0;

static int32 readData(Uint16 index);
static Uint16 readReg(Uint16 index, Uint16 addr);
static void writeReg(Uint16 index, Uint16 addr, Uint16 data);
static void writeCommand(Uint16 index, Uint16 command);


void ADS1256_Init()
{
    Uint16 i;

    memset(ads1256_data, 0, sizeof(ads1256_data));
    memset(ads1256_chan, 0, sizeof(ads1256_chan));

    SPI_init(SPI_MASTER, SPI_MODE, SPI_BRR(SPI_FREQ), 8);

    ADC_RESET();

    for (i = 0; i < ADC_COUNT; i++)
    {
        writeReg(i, REG_ADCON, 0);
        writeReg(i, REG_DRATE, DR_100SPS);
        #if !ADC_SELFCAL_EN
        writeReg(i, REG_OFC0, 0x00);
        writeReg(i, REG_OFC1, 0x00);
        writeReg(i, REG_OFC2, 0x00);
        writeReg(i, REG_FSC0, 0x08);
        writeReg(i, REG_FSC1, 0x40);
        writeReg(i, REG_FSC2, 0x49);
        #else
        writeCommand(i, CMD_SELFCAL);
        #endif
        DELAY_US(DRDY_BUSY_DELAY1);
        if (!(readReg(i, REG_STATUS) & STATUS_DRDY)) ads1256_error |= 1 << i;
    }
    DELAY_US(DRDY_BUSY_DELAY2);

    for (i = 0; i < ADC_COUNT; i++)
        if (readReg(i, REG_STATUS) & STATUS_DRDY) ads1256_error |= 1 << i;
}

void ADS1256_Update()
{
    Uint16 index, chan;

    SPI_init(SPI_MASTER, SPI_MODE, SPI_BRR(SPI_FREQ), 8);

    if (readReg(ads1256_num, REG_STATUS) & STATUS_DRDY) return;

    index = ads1256_num * ADC_CH_COUNT + ads1256_chan[ads1256_num];
    if (++ads1256_chan[ads1256_num] >= ADC_CH_COUNT) ads1256_chan[ads1256_num] = 0;
    chan = ads1256_chan[ads1256_num] << 1;

    writeReg(ads1256_num, REG_MUX, MUX_PSEL(chan) | MUX_NSEL(chan + 1));
    writeCommand(ads1256_num, CMD_SYNC);
    writeCommand(ads1256_num, CMD_WAKEUP);

    ads1256_data[index] = (readData(ads1256_num) << 8) >> 8;

    if (++ads1256_num >= ADC_COUNT) ads1256_num = 0;
    ads1256_status |= 1U << index;
}

static int32 readData(Uint16 index)
{
    int32 data;
    SELECT_SPI(index);
    SPI_send(CMD_RDATA);
    DELAY_US(READ_DELAY);
    data  = (Uint32)SPI_send(0) << 16;
    data |= (Uint32)SPI_send(0) << 8;
    data |= (Uint32)SPI_send(0);
    DELAY_US(CS_HIGH_DELAY);
    DESELECT_SPI(index);
    return data;
}

static Uint16 readReg(Uint16 index, Uint16 addr)
{
    Uint16 data;
    SELECT_SPI(index);
    SPI_send(CMD_RREG | addr);
    SPI_send(0);
    DELAY_US(READ_DELAY);
    data = SPI_send(0);
    DELAY_US(CS_HIGH_DELAY);
    DESELECT_SPI(index);
    return data;
}

static void writeReg(Uint16 index, Uint16 addr, Uint16 data)
{
    SELECT_SPI(index);
    SPI_send(CMD_WREG | addr);
    SPI_send(0);
    SPI_send(data);
    DELAY_US(CS_HIGH_DELAY);
    DESELECT_SPI(index);
}

static void writeCommand(Uint16 index, Uint16 command)
{
    SELECT_SPI(index);
    SPI_send(command);
    DELAY_US(CS_HIGH_DELAY);
    DESELECT_SPI(index);
}


