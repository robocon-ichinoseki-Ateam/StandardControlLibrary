#include "mbed.h"
#include "SBUS.h"

SBUS::SBUS(PinName tx, PinName rx) : sbus_(tx, rx)
{
    sbusIndex = 0;
    for (int i = 0; i < 18; i++)
        rcChannel[i] = 0;

    sbus_.baud(100000);
    sbus_.format(8, Serial::Even, 2);
    sbus_.attach(this, &SBUS::sbusIrqRx, Serial::RxIrq);
}

void SBUS::sbusIrqRx ()
{
    static uint8_t sbus[25] = {0};

    int val = sbus_.getc();


    if (sbusIndex == 0 && val != 0x0F) {
        return;
    }

    sbus[sbusIndex] = val;
    sbusIndex++;


    if (sbusIndex == 25) {
        sbusIndex = 0;

        if (sbus[24] != 0x0) {
            rcChannel[0] = ((sbus[1] | sbus[2] << 8) & 0x07FF);
            rcChannel[1] = ((sbus[2] >> 3 | sbus[3] << 5) & 0x07FF);
            rcChannel[2] = ((sbus[3] >> 6 | sbus[4] << 2 | sbus[5] << 10) & 0x07FF);
            rcChannel[3] = ((sbus[5] >> 1 | sbus[6] << 7) & 0x07FF);
            rcChannel[4] = ((sbus[6] >> 4 | sbus[7] << 4) & 0x07FF);
            rcChannel[5] = ((sbus[7] >> 7 | sbus[8] << 1 | sbus[9] << 9) & 0x07FF);
            rcChannel[6] = ((sbus[9] >> 2 | sbus[10] << 6) & 0x07FF);
            rcChannel[7] = ((sbus[10] >> 5 | sbus[11] << 3) & 0x07FF);
            rcChannel[8] = ((sbus[12] | sbus[13] << 8) & 0x07FF);
            rcChannel[9] = ((sbus[13] >> 3 | sbus[14] << 5) & 0x07FF);
            rcChannel[10] = ((sbus[14] >> 6 | sbus[15] << 2 | sbus[16] << 10) & 0x07FF);
            rcChannel[11] = ((sbus[16] >> 1 | sbus[17] << 7) & 0x07FF);
            rcChannel[12] = ((sbus[17] >> 4 | sbus[18] << 4) & 0x07FF);
            rcChannel[13] = ((sbus[18] >> 7 | sbus[19] << 1 | sbus[20] << 9) & 0x07FF);
            rcChannel[14] = ((sbus[20] >> 2 | sbus[21] << 6) & 0x07FF);
            rcChannel[15] = ((sbus[21] >> 5 | sbus[22] << 3) & 0x07FF);
        }
    }
}



int16_t SBUS::getData(uint8_t ch)
{
    return rcChannel[ch];
}

int SBUS::getStickVal(int axis)
{
    switch (axis) {
        case 0:
            return SBUS::map(getData(3), 368, 1680, -255, 255);
        case 1:
            return SBUS::map(getData(1), 368, 1680, 255, -255);
        case 2:
            return SBUS::map(getData(0), 368, 1680, -255, 255);
        case 3:
            return SBUS::map(getData(2), 368, 1680, -255, 255);
        default:
            return 0;
    }
}

int SBUS::getSwitchVal(int parm)
{
    return SBUS::map(getData(parm + 4), 144, 1904, 0, 2);
}

long SBUS::map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}