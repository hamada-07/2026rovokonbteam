#include "PID.h"
#include "shomona.h"
#include "main.h"



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
  float dt = ((float)(M->tick) / 1000.0f - (float)(last_tick) / 1000.0f);
  
  M->integral += ((float)(M->error) + (float)(last_error)) * dt / 2.0f;

  M->derivative = ((float)(M->error) - (float)(last_error)) / dt;

  if((M->speed==0)&&(absf(M->error) < 2000))M->power=0;
  

  int16_t P = limit(Kp * M->error     ,-10000,10000);
  int16_t I = limit(Ki * M->integral  ,-10000,10000);
  int16_t D = limit(Kd * M->derivative,-10000,10000);
  
  if(id==1){
    // print("P%d:",id);
    // print("%5d ",P);
    // print("I%d:",id);
    // print("%5d ",I);
    // print("D%d:",id);
    // print("%5d ",D);
  }

  M->power = limit(P + I + D,-10000,10000);
  if((M->target_speed==0)){
    M->power=0;
  }
}

