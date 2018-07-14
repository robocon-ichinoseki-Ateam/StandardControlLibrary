#ifndef MotorData_h
#define MotorData_h

#define GRAVITY 9.807
#define Nm2gfm (1/GRAVITY)
#define gfm2Nm GRAVITY

#define mNm2gfcm (Nm2gfm * 100)
#define gfcm2mNm (gfm2Nm / 100)

typedef struct
{
    double minVoltage;      //[V]
    double maxVoltage;      //[V]
    
    double voltage;         //[V]
    double current;         //[A]
    
    double rpm;             //[RPM]
    double torgle;          //[mN*m]
    
    double stallTorgle;     //[mN*m]
    double stallCurrent;    //[A] 
}motorData_t;

typedef struct
{
    double reductionRatio;          //
    double ratedMaxTorgle;          //[kgf*cm]
    double instantaneousMaxTorgle;  //[kgf*cm]
    double efficiency;              // 
}gearboxData_t;

#ifdef __cplusplus
extern "C" {
#endif

// return max speed [rpm]
double getMaxSpeed(motorData_t motor, gearboxData_t gearbox, double voltage);

// return max torgle []
double getMaxTorgle(motorData_t motor, gearboxData_t gearbox);

#ifdef __cplusplus
}
#endif

#endif //MotorData_h
