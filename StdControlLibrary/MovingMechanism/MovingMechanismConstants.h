#ifndef MovinMechanismConstants_h
#define MovinMechanismConstants_h

#define halfPi (PI / 2)
#define oneThirdrPi (PI / 3)
#define quarterPi (PI / 4)

typedef struct
{
    double theta;  // for omni
    double radius; // for omni
    double length; // for mecanum, steering
    double width;  // for mecanum, steering
    //double wheelRadius;
    int option;
}mechanismConfig_t;

typedef struct
{
    double minInput;  //最小機体速度
    double maxInput;  //最大機体速度
    double minOutput; //最小ホイール速度
    double maxOutput; //最大ホイール速度
}thresholdParam_t;

#endif //MovinMechanismConstants_h
