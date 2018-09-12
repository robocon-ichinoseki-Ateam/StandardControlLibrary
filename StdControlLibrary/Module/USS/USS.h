#ifndef USS_h
#define USS_h

#include "mbed.h"
class USS
{
  public:
    USS(PinName echoPin, PinName trigPin, double timeout = calcuTimeOfDistance(8.0));

    static double calcuTimeOfDistance(double distance);
    static double calcuTimeOfDistance_ms(double distance);
    static double calcuTimeOfDistance_us(double distance);

    void setAutoUpdate(bool isOn);
    void start();
    bool isData();
    double getDistance();

    void fall(void (*fptr)(void));
    void rise(void (*fptr)(void));

  protected:
    void isr_rise();
    void isr_fall();
    void timeout();

  protected:
    double _timeout;
    Timer _timer;
    Timeout _timeoutTimer;
    DigitalOut _trigPin;
    InterruptIn _echoPin;

    Ticker TrigerTiming;
    void Triger();

    double _distance;
    bool _isData;
    bool _isAutoUpdate;
};

#endif //USS_h