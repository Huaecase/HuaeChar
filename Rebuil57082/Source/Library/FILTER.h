#ifndef FILTER_H
#define FILTER_H

//2阶滤波 结构体 定义
typedef struct 
{
	float b0, b1, b2, a1, a2;
	float d1, d2;
	
} BiFilter;

void BiFilter_LP_Init(BiFilter *filter);    //低通滤波器 初始化      参数需要调试；
float BiFilterIn(BiFilter *filter, float input);  // 输入滤波;

#endif