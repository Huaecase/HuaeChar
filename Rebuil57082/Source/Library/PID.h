// 

#ifndef PID_H
#define PID_H

typedef struct 
{
	float SetValue;    //期望值
	float output;      // 被调量
	
	float kp;
	float ki;
	float kd;
	
	float Ek;     // 当前误差
  float Ek1;   //  上次误差
  float Ek2;	// 上上次误差
 
}PID;

void PID_init(PID * P,float p,float i,float d);// 
void PID_SetValue(PID * P,float setval);
int PID_Inc(PID *P,float ActualValue);

#endif