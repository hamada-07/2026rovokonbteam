#ifndef PID_H
#define PID_H

#include "stm32g4xx_hal.h"
#include <stdint.h>
#include <sys/types.h>


typedef struct {
    int16_t encoder;
    int16_t speed;
    float integral;
    int16_t derivative;
    int16_t tick;
    int16_t target_speed;
    int16_t error;
    int16_t power;
} motor;

void PID(motor *M, int16_t prev_speed, float Kp, float Ki, float Kd);
void motor_init(motor *M);
void SetTargetSpeed(motor *M, int16_t target_speed);

#endif