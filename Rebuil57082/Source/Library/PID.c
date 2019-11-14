#include "PID.h"

void PID_init(PID * P,float p,float i,float d)
{
	P-> SetValue=0;    //期望值
	P-> output=0;    // 被调量 要改为0
	
	P-> kp=p;
	P-> ki=i;
	P-> kd=d;
	
	P-> Ek=0;     // 当前误差
    P-> Ek1=0;   //  上次误差
    P-> Ek2=0;	// 上上次误差
	
}
void PID_SetValue(PID * P,float setval)
{
	P-> SetValue=setval; 
}

int PID_Inc(PID *P,float ActualValue)
{
	float PID_Inc;
	P->Ek=P->SetValue-ActualValue;
	PID_Inc=P->kp*(P->Ek - P->Ek1)+ P->ki* P->Ek+P->kd*(P->Ek-2*P->Ek1+P->Ek2);
	P->output+=PID_Inc;
	
	P->Ek2=P->Ek1;
	P->Ek1=P->Ek;
	return 1;
}