# MotorData

## 定数
```C++
#define GRAVITY 9.807
#define Nm2gfm (1/GRAVITY)
#define gfm2Nm GRAVITY

#define mNm2gfcm (Nm2gfm * 100)
#define gfcm2mNm (gfm2Nm / 100)
```

## モーターデータ構造
```C++
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
```

## ギアボックスデータ構造
```C++
typedef struct
{
    double reductionRatio;          //
    double ratedMaxTorgle;          //[kgf*cm]
    double instantaneousMaxTorgle;  //[kgf*cm]
    double efficiency;              // 
}gearboxData_t;
```