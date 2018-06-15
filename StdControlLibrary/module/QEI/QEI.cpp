#include "QEI.h"

//UM p329～

QEI::QEI(PinName phaseA, 
        PinName phaseB, 
        PinName index, 
        uint32_t pulsePerRotation, 
        Encoding encoding,
        SignalMode signalMode):
    _phaseA(phaseA), _phaseB(phaseB), _index(index),
    _encoding(encoding), _signalMode(signalMode)
{
    // Basic configration
    qei_init(&_qei, _phaseA, _phaseB, _index);
    
    // Set pulse num per revolution
    uint32_t maxPos = pulsePerRotation;
    switch(_encoding)
    {
        case X2_ENCODING: 
            maxPos *= 2; 
            maxPos -= 1;
            break;
        case X4_ENCODING: 
            maxPos *= 4;
            maxPos -= 1;
            break;
        default:
            maxPos = 0;
    }
    setMaxPos(maxPos);
    
    // Set encoding
    setEncoding(_encoding);
    
    // Set signal mode
    setSignalMode(_signalMode);
    
    // Set default velocity capture period
    setVelocityTimerPeriod_us(1000);
    
    // Peripheral reset
    reset();
}

QEI::~QEI()
{
    // Distaching interrupts
    for(int irq = 0; irq < IrqCnt; irq++)
        attach(NULL, (IrqType)irq);
    
}

void QEI::reset()
{
    qei_reset();
}

////////////////////////// set //////////////////////////

void QEI::setMaxPos(uint32_t num)
{
    qei_set_maxpos(&_qei, num);
}

void QEI::setInvertDirection(bool isInvert)
{
    qei_set_invert_direction(isInvert);
}

void QEI::setInvertIndex(bool isInvert)
{
    qei_set_invert_index(isInvert);
}

void QEI::setSignalMode(SignalMode signalMode)
{
    qei_set_signal_mode((QEISignalMode)signalMode);
}

void QEI::setEncoding(Encoding encoding)
{
    qei_set_encoding(&_qei, (QEIEncoding)encoding);
}

// What is Bit 3 of LPCQEI->CONF ?

void QEI::setVelocityTimerPeriod_us(uint32_t us)
{
#warning find period to value.
    // p346 22.7.3 example
    // load = PCLK / キャプチャー周波数
    uint32_t regVal = ((double)_qei.PCLK * us / 1000000);
    
    if(regVal == 0)
        regVal = 1;
        
    qei_set_timer_load(&_qei, regVal);
}

////////////////////////// get //////////////////////////
/*
uint32_t QEI::getInterrupts()
{
    return LPC_QEI->IE;
}

uint32_t QEI::getInterruptStatus()
{
    return LPC_QEI->INTSTAT;
}
*/

/*
int QEI::getPhase(Channel channel)
{
    uint32_t phaseState = LPC_QEI->CONF;
    switch(channel)
    {
        case Phase_A: 
            if(phaseState & (1 << 17) || phaseState & (1 << 16))
                return 1;
            else
                return 0;
            
        case Phase_B: 
            if(phaseState & (1 << 18) || phaseState & (1 << 17))
                return 1;
            else
                return 0; 
    }
    return -1;
}*/

int QEI::getDirection()
{
    int value = 0;
    
    if(getVelocity())
    {
        value = (LPC_QEI->STAT & 0x00000001) ? -1 : 1;
        
        if(getInvertDirection())
            value *= -1;
    }
    return value;
}

uint32_t QEI::getPosition()
{
    return qei_get_position();
}

uint32_t QEI::getIndex()
{
    return qei_get_index();
}

uint32_t QEI::getVelocity()
{
    return qei_get_velocity();
}

double QEI::getRotation()
{
    return ((double)getPosition() / (_qei.maxPos + 1));
}

double QEI::getRPM()
{
    return (60 * getRPS());
}

double QEI::getRPS()
{
    /*
    RPM = (PCLK * Speed * 60) / (Load * PPR * Edges)
    
    PCLK is the QEI controller clock. 
    PPR is the number of pulses per revolution of the physical encoder.
    Edges 2 or 4 (x2 or x4)
    
    PPR * Edges = 400?
    */
    
    double rps = ( (double)_qei.PCLK  * getVelocity() ) / ( _qei.load * (_qei.maxPos + 1) );
    return rps;
}

bool QEI::getInvertDirection()
{
    return qei_get_invert_direction_status();
}

bool QEI::getInvertIndex()
{
    return qei_get_invert_index_status();
}

////////////////////////// Irq //////////////////////////

void QEI::attach(Callback<void()> func, IrqType type)
{
    
}
/*
void QEI::setInterrupts(uint32_t symbol)
{
    LPC_QEI->IES |= symbol;
}

void QEI::clearInterrupts(uint32_t symbol)
{
    LPC_QEI->IEC |= symbol;
}

void QEI::setInterruptStatus(uint32_t symbol)
{
    LPC_QEI->SET |= symbol;
}

void QEI::clearInterruptStatus(uint32_t symbol)
{
    LPC_QEI->CLR |= symbol;
}
*/
