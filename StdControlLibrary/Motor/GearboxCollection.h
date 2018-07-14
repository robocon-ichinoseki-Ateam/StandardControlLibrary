#ifndef GearboxCollection_h
#define GearboxCollection_h

#include "MotorData.h"

// http://suzakugiken.jp/goods/30144/catalog-IG32.pdf
// http://suzakugiken.jp/goods/30335/catalog-IG36P.pdf
// http://suzakugiken.jp/goods/30045/catalog-IG42C.pdf

static gearboxData_t noGearbox =
{
    .reductionRatio = (double)1,
};

static gearboxData_t IG32_27 =
{
    .reductionRatio = (double)103/121,
    .ratedMaxTorgle = 6.0,
    .instantaneousMaxTorgle = 18.0,
    .efficiency = 0.7,
};

static gearboxData_t IG32_71 =
{
    .reductionRatio = (double)524/3179,
    .ratedMaxTorgle = 8.0,
    .instantaneousMaxTorgle = 24.0,
    .efficiency = 0.6,
};

static gearboxData_t IG32_100 =
{
    .reductionRatio = (double)1044/2057,
    .ratedMaxTorgle = 10.0,
    .instantaneousMaxTorgle = 30.0,
    .efficiency = 0.6,
};

#endif //GearboxCollection_h
