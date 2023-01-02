/*-----------------------------------------------------------------------------------------------------
【平 台】Keil
【适 用 单 片 机】msp432P401R
【底 层 库】msp432_driverlib_3_21_00_05
【开 发】lv
* @@ 库仅供参考 后果自负
* 板载舵机资源介绍
* 10.5(TimerA3_CH1:servo3)   5.7(TimerA2_CH2:servo2)   5.6(TimerA2_CH1:servo1)
* 舵机占空比范围5%-12.5%  所以这里占空比值range 500 - 2500
* 版本 v1.0
* 时间 2022年12月27日16:39:03
-------------------------------------------------------------------------------------------------------*/
#include "main.h"

/// @brief 舵机初始化
/// @param Servox servo1  servo2  servo3  
void Servo_Init(Servox Servox)
{
    switch (Servox)
    {
    case Servo1:
        TimerA_PWM_Init(TimeA2, TimerAx_CH1);
        PWMConfig.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
        PWMConfig.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_48;
        PWMConfig.compareOutputMode = TIMER_A_OUTPUTMODE_TOGGLE_SET;
        PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
        PWMConfig.dutyCycle = 1000;              //初始占空比值为1000
        PWMConfig.timerPeriod = 20000 - 1;       //50Hz
        Timer_A_generatePWM(TIMER_A2_BASE, &PWMConfig);
        break;
    case Servo2:
        TimerA_PWM_Init(TimeA2, TimerAx_CH2);
        PWMConfig.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
        PWMConfig.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_48;
        PWMConfig.compareOutputMode = TIMER_A_OUTPUTMODE_TOGGLE_SET;
        PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;
        PWMConfig.dutyCycle = 1000;              
        PWMConfig.timerPeriod = 20000 - 1;    //50Hz
        Timer_A_generatePWM(TIMER_A2_BASE, &PWMConfig);
        break;
    case Servo3:
        TimerA_PWM_Init(TimeA3, TimerAx_CH1);
        PWMConfig.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
        PWMConfig.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_48;
        PWMConfig.compareOutputMode = TIMER_A_OUTPUTMODE_TOGGLE_SET;
        PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
        PWMConfig.dutyCycle = 1000;             
        PWMConfig.timerPeriod = 20000 - 1;    //50Hz
        Timer_A_generatePWM(TIMER_A3_BASE, &PWMConfig);
        break;    
    }
    
}

/// @brief 设置舵机的占空比
/// @param Servox 舵机号 servo1  servo2  servo3  
/// @param compareValue range  500 - 2500
void Servo_SetPWM(Servox Servox, uint_fast16_t compareValue )
{
    switch (Servox)
    {
    case Servo1:
        if(compareValue >= 2500)  compareValue = 2500;
        else if(compareValue <= 500) compareValue = 500;
        Timer_A_setCompareValue(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, compareValue);
        break;
    case Servo2:
        if(compareValue >= 2500)  compareValue = 2500;
        else if(compareValue <= 500) compareValue = 500;
        Timer_A_setCompareValue(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, compareValue);
        break;
    case Servo3:
        if(compareValue >= 2500)  compareValue = 2500;
        else if(compareValue <= 500) compareValue = 500;
        Timer_A_setCompareValue(TIMER_A3_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, compareValue);
        break;    
    
    }
}