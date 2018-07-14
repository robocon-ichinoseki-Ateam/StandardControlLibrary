#ifndef MotorCollection_h
#define MotorCollection_h

#include "MotorData.h"

static motorData_t RS_380_S = 
{
    .minVoltage = 6.6,
    .maxVoltage = 7.2,
    
    .voltage = 7.2,
    //.current = ,
    
    //.rpm = ,
    .torgle = 129 * gfcm2mNm,
    
    //.stallTorgle = ,
    //.stallCurrent = ,
};

static motorData_t RS_540_SH = 
{
    .minVoltage = 4.8,
    .maxVoltage = 12.0,

    .voltage = 7.2,
    .current = 6.0,
    
    .rpm = 14000,
    .torgle = 19.6,
    
    //.stallTorgle = ,
    //.stallCurrent = ,  
};

static motorData_t RS_540_J = 
{
    .minVoltage = 4.8,
    .maxVoltage = 12.0,
    
    .voltage = 7.2,
    .current = 7.2,
        
    .rpm = 14500,
    .torgle = 25.0,
    
    //.stallTorgle = ,
    //.stallCurrent = ,  
};

/*
static motorData_t RS_775_ = 
{
    .minVoltage = ,
    .maxVoltage = ,

    .voltage = 18,
    .current = ,
    
    .rpm = ,
    .torgle = ,
    
    .stallTorgle = ,
    .stallCurrent = ,
}
*/

#endif //MotorCollection_h
