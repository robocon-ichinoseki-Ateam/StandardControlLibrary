#include "mbed_assert.h"
#include <math.h>
#include <string.h>

#include "qei_api.h"
#include "cmsis.h"
#include "pinmap.h"
#include "mbed_error.h"

static int qei_used = 0;
static int get_available_qei(void) {
    int i;
    for (i = 0; i < 1; i++) {
        if ((qei_used & (1 << i)) == 0)
            return i;
    }
    return -1;
}

static void switch_pin(PinName phA, PinName phB, PinName Idx)
{    
    // Set PHA
    if(phA != NC)
    {
        LPC_SWM->PINASSIGN14 &= 0xFFFF00FF;
        LPC_SWM->PINASSIGN14 |= ((int)phA << 8);
    }
    if(phB != NC)
    {
        LPC_SWM->PINASSIGN14 &= 0xFF00FFFF;
        LPC_SWM->PINASSIGN14 |= ((int)phB << 16);
    }
    if(Idx != NC)
    {
        LPC_SWM->PINASSIGN14 &= 0x00FFFFFF;
        LPC_SWM->PINASSIGN14 |= ((int)Idx << 24);
    }
}

void qei_init(qei_t *obj, PinName phA, PinName phB, PinName Idx)
{
    int qei_n = get_available_qei();
    if(qei_n == -1)
    {
        error("No available QEI");
    }
    
    switch_pin(phA, phB, Idx);
    
    // Enable QEI clock
    LPC_SYSCON->SYSAHBCLKCTRL1 |= (1 << 21);
    
    // Peripheral reset
    LPC_SYSCON->PRESETCTRL1 |= (1 << 21);
    LPC_SYSCON->PRESETCTRL1 &= ~(1 << 21);
    
    // store QEI control clock
#warning
    obj->PCLK = SystemCoreClock / LPC_SYSCON->SYSAHBCLKDIV;
    //PCLK = 12000000 / LPC_SYSCON->SYSAHBCLKDIV;
    
}

void qei_free()
{
    // ToDo
}

void qei_reset()
{
    /* 
    Reset position counter (Bit 0), 
          position counter on index (Bit 1), 
          velocity (Bit 2), 
          index counter (Bit 3)
    */
    LPC_QEI->CON = 0xF;
}

//////////////////////// set //////////////////////////
void qei_set_maxpos(qei_t *obj, uint32_t num)
{
    LPC_QEI->MAXPOS = num;
    obj->maxPos = num;
}

void qei_set_invert_direction(bool is_invert)
{
    LPC_QEI->CONF &= ~(1 << 0);
    LPC_QEI->CONF |= is_invert;
}

void qei_set_invert_index(bool is_invert)
{
    LPC_QEI->CONF &= ~(1 << 3);
    LPC_QEI->CONF |= is_invert; 
}

void qei_set_signal_mode(QEISignalMode mode)
{
    switch(mode)
    {
        case QUADRATURE_ENCODER:      LPC_QEI->CONF &= ~(1 << 1); break;
        case DIRECTION_CLOCK_ENCODER: LPC_QEI->CONF |= (1 << 1);  break;
    }
}

void qei_set_encoding(qei_t *obj, QEIEncoding encoding)
{
    switch(encoding)
    {
        case X2_ENCODING: 
            LPC_QEI->CONF &= ~(1 << 2);
            obj->encoding = 2;
            break;
        case X4_ENCODING:
            LPC_QEI->CONF |= (1 << 2);
            obj->encoding = 4;
            break;
    }
}

void qei_set_timer_load(qei_t *obj, uint32_t val)
{
    LPC_QEI->LOAD = val;
    obj->load = val;
}

//////////////////////// get //////////////////////////
bool qei_get_direction()
{
#warning false : true?
    bool val = (LPC_QEI->STAT & 0x00000001) ? true : false; // false : true?
    return val;
}

uint32_t qei_get_position()
{
    return LPC_QEI->POS;
}

uint32_t qei_get_index()
{
    return LPC_QEI->INXCNT;
}

uint32_t qei_get_velocity()
{
    return LPC_QEI->CAP;
}

bool qei_get_invert_direction_status()
{
    return (LPC_QEI->CONF & (1 << 0));
}

bool qei_get_invert_index_status()
{
    return (LPC_QEI->CONF & (1 << 3));
}