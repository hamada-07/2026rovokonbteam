#ifndef SBUS_H
#define SBUS_H

#include "stm32g4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef enum {
    SBUS_VR,
    SBUS_SW,
    SBUS_RAW
} sbus_type_t;

int sbus_available(void);

void sbus_init(UART_HandleTypeDef *huart);

void sbus_set(uint8_t ch, sbus_type_t t);

float sbus_get(uint8_t ch);

void sbus_update(void);

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif