#ifndef MovinMechanismConstants_h
#define MovinMechanismConstants_h

#define halfPi (PI / 2)
#define oneThirdrPi (PI / 3)
#define quarterPi (PI / 4)

typedef struct
{
    double theta;
    double radius;
    double wheelRadius;
    int option;
}mechanismConfig_t;

typedef struct
{
    double minInput;  //入力の切り捨て閾値
    double maxInput;  //入力の最大値
    double minOutput; //出力の切り捨て閾値
    double maxOutput; //出力の最大値、出力結果は[-maxOutputVelocity .. maxOutputVelocity]
}thresholdParam_t;

#endif //MovinMechanismConstants_h
