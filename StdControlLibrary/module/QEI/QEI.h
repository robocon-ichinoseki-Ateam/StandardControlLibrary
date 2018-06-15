#ifndef QEI_h
#define QEI_h

#include "qei_api.h"

#include "mbed.h"

class QEI
{
public:
    enum Dirction
    {
        forward,
        reverse
    };
    
    enum Encoding
    {
        X2_ENCODING,
        X4_ENCODING
    };
    
    enum SignalMode
    {
        QUADRATURE_ENCODER,
        DIRECTION_CLOCK_ENCODER
    };
    
    enum IrqType
    {
        INT_INT = 0,    // pulse was detected
        TIM_INT,        // velocity timer overflow
        VELC_INT,       // velocity is less than compare velocity
        DIR_INT,        // change dirction
        ERR_INT,        // encoder phase error
        ENCLK_INT,      // encoder clock pulse detected
        POS0_INT,       // position is equal to the compare value (Ch 0)
        POS1_INT,       // (Ch 1)
        POS2_INT,       // (Ch 2)
        REV0_INT,       // index is equal to the compare value (Ch 0)
        POS0REV_INT,    // POS0_INT && REV0_INT
        POS1REV_INT,    // (Ch 1)
        POS2REV_INT,    // (Ch 2)
        REV1_INT,       // (Ch 1)
        REV2_INT,       // (Ch 2)
        MAXPOS_INT,     // position value is more than MAXPOS or less than 0
        
        IrqCnt
    };
    
public:
    QEI(PinName phaseA, 
        PinName phaseB, 
        PinName index, 
        uint32_t pulsePerRotation, 
        Encoding encoding = X4_ENCODING,
        SignalMode signalMode = QUADRATURE_ENCODER);
    ~QEI();
        
    void reset();
    
    // set parameter
    
    void setMaxPos(uint32_t num);
    void setInvertDirection(bool isInvert);
    void setInvertIndex(bool isInvert);
    void setSignalMode(SignalMode signalMode);
    void setEncoding(Encoding encoding);
    
    void setVelocityTimerPeriod_us(uint32_t us);
    
    
    // get value
    //int getPhase(Channel channel);
    int getDirection();
    uint32_t getIndex();
    double getRotation();
    double getRPM();
    double getRPS();

    bool getInvertDirection();
    bool getInvertIndex();
    
    // Interrupts
    /*
    uint32_t getInterrupts();
    uint32_t getInterruptStatus();
    void setInterrupts(uint32_t symbol);
    void clearInterrupts(uint32_t symbol);
    void setInterruptStatus(uint32_t symbol);
    void clearInterruptStatus(uint32_t symbol);
    */
    
    void attach(Callback<void()> func, IrqType type = INT_INT);
    
    template<typename T>
    void attach(T *obj, void (T::*method)(), IrqType type = INT_INT) {
        attach(callback(obj, method), type);
    }
    
    template<typename T>
    void attach(T *obj, void (*method)(T*), IrqType type = INT_INT)
    {
        attach(callback(obj, method), type);
    }

protected:
    uint32_t getPosition();
    uint32_t getVelocity();
    uint32_t getPCLK() { return _qei.PCLK; }

protected:
    PinName _phaseA, _phaseB, _index;
    Encoding _encoding;
    SignalMode _signalMode;
    
    qei_t _qei;
    Callback<void()> _irq[IrqCnt];
    
    //int PPR;
    //int PCLK;
};

#endif //QEI_h