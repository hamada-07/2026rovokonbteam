#include "omni.h"
#include "main.h"
#include <math.h>


double Omni(double front,double side,double ang,int id){//1から右上、左上、右下、左下
  int lefthiju=3,righthiju=1;
  double num;
  
  switch(id){
    case 0:
      num =  righthiju*ang - lefthiju*sqrt(front*front + side*side)*sin(atan2(front, side) - M_PI/4)/sqrt(2);
      break;
    case 1:
      num =  righthiju*ang + lefthiju*sqrt(front*front + side*side)*cos(atan2(front, side) - M_PI/4)/sqrt(2);
      break;
    case 2:
      num =  righthiju*ang - lefthiju*sqrt(front*front + side*side)*cos(atan2(front, side) - M_PI/4)/sqrt(2);
      break;
    case 3:
      num =  righthiju*ang + lefthiju*sqrt(front*front + side*side)*sin(atan2(front, side) - M_PI/4)/sqrt(2);
      break;
    default:
      num = 0;
      print("omni error!!!",0);
  }
  
  return num/(lefthiju+righthiju);
}