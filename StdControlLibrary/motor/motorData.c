#include "motorData.h"

double getMaxSpeed(motorData_t motor, gearboxData_t gearbox)
{
    return motor.rpm * gearbox.reductionRatio;
}

double getMaxTorgle(motorData_t motor, gearboxData_t gearbox)
{
    return motor.torgle / gearbox.reductionRatio;
}