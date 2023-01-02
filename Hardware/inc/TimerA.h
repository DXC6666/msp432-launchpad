/*-----------------------------------------------------------------------------------------------------
【平 台】Keil
【适 用 单 片 机】msp432P401R
【底 层 库】msp432_driverlib_3_21_00_05
【开 发】lv
* @@ 库仅供参考 后果自负
* 板载定时器A资源介绍
* 
* 
* 版本 v1.0
* 时间 2022年12月27日16:39:03
-------------------------------------------------------------------------------------------------------*/
#ifndef __TIMERA_H__
#define __TIMERA_H__



typedef enum
{
    TimeA0,
    TimeA1,
    TimeA2,
    TimeA3,
}TimeAx ;

typedef enum
{
    TimerAx_CH0,
    TimerAx_CH1,
    TimerAx_CH2,
    TimerAx_CH3,
    TimerAx_CH4
}TimerAx_CHx;

extern Timer_A_PWMConfig PWMConfig;

void TimerA_INT_Init(TimeAx TimeAx, uint32_t TIMER_PERIOD);
void TimerA_PWM_Init(TimeAx TimeAx, TimerAx_CHx TimerAx_CHx);
#endif