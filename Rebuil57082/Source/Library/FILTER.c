#include"FILTER.h"

void BiFilter_LP_Init(BiFilter *filter)
{
//Fc=5Hz,Q=,Fs= K;  根据 ADC转换周期 以及 滤波 中心频率计算：
//	采样率：64/ADCFre，中心频率 5Hz
		filter->a1= -1.998615912105303980;
		filter->a2=0.998616438259541717;
		filter->b0= 0.340698901720978442;
		filter->b1= -0.681397277287719039;
		filter->b2=0.340698901720978442;
    // zero initial samples
        filter->d1 = filter->d2 = 0;
}

/* Computes a BiFilter filter on a sample */

float BiFilterIn(BiFilter *filter, float input)
{
	float result;
	
    result = filter->b0 * input + filter->d1;
    filter->d1 = filter->b1 * input - filter->a1 * result + filter->d2;
    filter->d2 = filter->b2 * input - filter->a2 * result;
    return result;
}

//void biquad_NOTCH1_Init(BiFilter *filter)
//{
//    // Init the coefficients
//    //Fc=260Hz,BW=100Hz,Q=1.26867,Fs=1K;
//    filter->b0 = 0.717702064568570f;
//    filter->b1 = 0.090129771003042f;
//    filter->b2 = 0.717702064568570f;
//    filter->a1 = 0.090129771003042f;
//    filter->a2 = 0.435404129137139f;
//    // zero initial samples
//    filter->d1 = filter->d2 = 0;
//}

