
#include "DSP28x_Project.h"
#include "lir_da158a_02.h"

#define SPI_FREQ            800000
#define SPI_MODE            SPI_MODE2

#define SELECT_SPI()        GpioDataRegs.GPADAT.bit.GPIO1 = 0
#define DESELECT_SPI()      GpioDataRegs.GPADAT.bit.GPIO1 = 1

Uint16 lir_num_bits = 12;
int32  lir_position = 0;
int32  lir_offset = 0;


void LIR_158A_02_Update()
{
    Uint32 gray = 0, data, bit_mask;
    Uint16 i, num_bytes, num_bits, bit_shift;

    num_bytes = (lir_num_bits + 8) >> 3;
    num_bits  = num_bytes << 3;
    bit_mask  = (1UL << lir_num_bits);
    bit_shift = num_bits - lir_num_bits - 1;

    SPI_init(SPI_MASTER, SPI_MODE, SPI_BRR(SPI_FREQ), 8);

    SELECT_SPI();
    for(i = 0; i < num_bytes; i++) { gray = gray << 8; gray |= SPI_send(0); }
    DESELECT_SPI();

    gray = (gray >> bit_shift) & (bit_mask - 1);
    for(data = 0; gray; gray=gray>>1) data ^= gray;

    lir_position = (int32)data - lir_offset;
    if (lir_position < 0) lir_position += bit_mask;
}


