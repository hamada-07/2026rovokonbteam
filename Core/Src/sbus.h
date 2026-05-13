#ifndef SBUS_H
#define SBUS_H

#include "stm32g4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define SBUS_CH 10

typedef enum {
    SBUS_VR,
    SBUS_SW,
    SBUS_RAW
} sbus_type_t;

static UART_HandleTypeDef *u;
static uint8_t rx[25];

static float val[SBUS_CH];
static sbus_type_t type[SBUS_CH];

static volatile int sbus_ready = 0;


void sbus_init(UART_HandleTypeDef *huart)
{
    u = huart;

    for (int i = 0; i < SBUS_CH; i++) {
        val[i] = 0.0f;
        type[i] = SBUS_RAW;
    }

    sbus_ready = 0;
    HAL_UART_Receive_IT(u, rx, 25);
}


void sbus_set(uint8_t ch, sbus_type_t t)
{
    if (ch < 5 || ch >= SBUS_CH+1) return;
    type[ch-1] = t;
}

static void decode(uint8_t *buf)
{
    int sp = 0;
    bool b[192];
    uint8_t d[25];
    int chd[SBUS_CH];

    for (int i = 0; i < 24; i++) {
    	if(buf[0] != 0x0F) return;
            sp = i;
            break;
    }

    for (int i = 0; i < 25; i++) {
        d[i] = buf[(i + sp) % 25];
    }

    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 8; j++) {
            b[i * 8 + j] = d[i + 1] & (1 << j);
        }
    }

    for (int i = 0; i < SBUS_CH; i++) {
        chd[i] = 0;
        for (int j = 0; j < 11; j++) {
            chd[i] |= b[i * 11 + j] << j;
        }
    }

    for (int i = 0; i < 4; i++) {
        val[i] = (float)(chd[i] - 1024) / 656;
    }

    for (int i = 4; i < SBUS_CH; i++) {
        switch (type[i]) {
        case SBUS_VR:
            val[i] = (float)(chd[i] - 144) / (1904 - 144);
            break;
        case SBUS_SW:
            if (chd[i] < 600) val[i] = 0.0f;
            else if (chd[i] < 1400) val[i] = 0.5f;
            else val[i] = 1.0f;
            break;
        default:
            val[i] = (float)chd[i];
            break;
        }
    }
}
float sbus_get(uint8_t ch)
{
    if (ch >= SBUS_CH+1) return 0.0f;
    return val[ch-1];
}
int sbus_available(void)
{
    return sbus_ready;
}

void sbus_update(void)
{
    if(sbus_ready){
        sbus_ready = 0;
        decode(rx);
    }
}
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if(huart == u)
    {
        __HAL_UART_CLEAR_OREFLAG(u);
        __HAL_UART_CLEAR_NEFLAG(u);
        __HAL_UART_CLEAR_FEFLAG(u);

        HAL_UART_Receive_IT(u, rx, 25);
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == u) {
        sbus_ready = 1;
        HAL_UART_Receive_IT(u, rx, 25);
    }
}
#endif

















