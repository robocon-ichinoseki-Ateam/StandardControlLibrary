#include "MotorData.h"

double getMaxSpeed(motorData_t motor, gearboxData_t gearbox, double voltage)
{
    return motor.rpm * gearbox.reductionRatio * voltage / motor.voltage;
}

double getMaxTorgle(motorData_t motor, gearboxData_t gearbox)
{
    return motor.torgle / gearbox.reductionRatio;
}
