#ifndef SBUS_H
#define SBUS_H

#include "stm32g4xx_hal.h"
#include <stdint.h>

#define SBUS_CH 10

typedef enum {
    SBUS_VR,
    SBUS_SW,
    SBUS_RAW
} sbus_type_t;

void sbus_init(UART_HandleTypeDef *huart);
void sbus_set(uint8_t ch, sbus_type_t type);
void sbus_update(void);
float sbus_get(uint8_t ch);

void sbus_stick(float* lf,float* ls,float* rf,float* rs);

extern uint8_t rx[25];

#endif