#include "omni.h"
#include <math.h>

double Omni(double front,double side,double ang,int id){//1から右上、左上、右下、左下
  
  double num;
  switch(id){
    case 0:
      num = -2*sqrt(front*front + side*side)*sin(atan2(front, side) - M_PI/4)/sqrt(2) + ang;
      break;
    case 1:
      num =  2*sqrt(front*front + side*side)*cos(atan2(front, side) - M_PI/4)/sqrt(2) + ang;
      break;
    case 2:
      num = -2*sqrt(front*front + side*side)*cos(atan2(front, side) - M_PI/4)/sqrt(2) + ang;
      break;
    case 3:
      num =  2*sqrt(front*front + side*side)*sin(atan2(front, side) - M_PI/4)/sqrt(2) + ang;
      break;
    default:
      num = 0;
      print("omni error!!!",0);
  }
  
  return num/3;
}