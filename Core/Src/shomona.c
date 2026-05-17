float limit(float p,float min,float max){
  if(p>max)p=max;
  if(p<min)p=min;
  return p;
}
float dead(float p,float min,float max){
  if((min < p)&&(p < max))p=0;
  return p;
}
float absf(float a){
  if(a<0)a *= -1.0f;
  return a;
}