#ifndef _QEI_API_H_
#define _QEI_API_H_

#include "device.h"
#include "stdbool.h"
/*
#include "hal/buffer.h"
#include "hal/dma_api.h"
*/

typedef enum
{
    X2_ENCODING,
    X4_ENCODING
} QEIEncoding;
    
typedef enum
{
    QUADRATURE_ENCODER,
    DIRECTION_CLOCK_ENCODER
} QEISignalMode;
    
typedef enum
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
} QEIIrqType;


struct qei_s
{
    int maxPos;
    int PCLK;
    int encoding;
    uint32_t load;
};

typedef struct qei_s qei_t;

#ifdef __cplusplus
extern "C" {
#endif

void qei_init(qei_t *obj, PinName phA, PinName phB, PinName Idx);
void qei_free(void);
void qei_reset(void);

void qei_set_maxpos(qei_t *obj, uint32_t num);
void qei_set_invert_direction(bool is_invert);
void qei_set_invert_index(bool is_invert);
void qei_set_signal_mode(QEISignalMode mode);
void qei_set_encoding(qei_t *obj, QEIEncoding encoding);
void qei_set_timer_load(qei_t *obj, uint32_t val);

bool qei_get_direction(void);
uint32_t qei_get_position(void);
uint32_t qei_get_index(void);
uint32_t qei_get_velocity(void);
bool qei_get_invert_direction_status(void);
bool qei_get_invert_index_status(void);

#ifdef __cplusplus
}
#endif

#endif //_QEI_API_H_
