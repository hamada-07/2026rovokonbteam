#include "PID.h"
#include "shomona.h"
#include "main.h"

#define limitnum 14000

void motor_init(motor *M) {
    M->encoder = 0;
    M->speed = 0;
    M->integral = 0;
    M->derivative = 0;
    M->tick = 0;
    M->target_speed = 0;
    M->error = 0;
    M->power = 0;
}
void SetTargetSpeed(motor *M, int16_t target_speed) {
  M->target_speed = target_speed;
}

void PID(motor *M, int16_t prev_speed, float Kp, float Ki, float Kd){
  static int id = 0;
  if(++id > 4) id = 1;
  
  int16_t last_error = M->error;
  uint32_t last_tick = M->tick;
  
  M->speed = prev_speed;
  M->error = M->target_speed - M->speed;
  M->tick = HAL_GetTick();
  float dt = (M->tick - last_tick) / 1000.0f;
  if(dt <= 0) dt = 0.001f;
  
  M->integral += ((float)(M->error) + (float)(last_error)) * dt / 2.0f;

  M->integral = limitf(M->integral,-14000 / Ki,14000 / Ki);

  M->derivative = ((float)(M->error) - (float)(last_error)) / dt;

  int16_t P = (int)(limit(Kp * M->error     ,-1*limitnum,limitnum));
  int16_t I = (int)(limit(Ki * M->integral  ,-1*limitnum,limitnum));
  int16_t D = (int)(limit(Kd * M->derivative,-1*limitnum,limitnum));
  
  if(id==1){
    print("%d,",P);
    print("%d,",I);
    print("%d,",D);
  }

  M->power = P + I + D;

  // if((M->speed==0)&&(absf(M->error) < 2000))M->power=0;
  // if((M->speed==0)&&(absf(M->error) < 2000))M->integral=0;

  if((M->target_speed == 0)){
    M->power=0;
  }
}

