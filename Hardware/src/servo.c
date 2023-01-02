/*-----------------------------------------------------------------------------------------------------
��ƽ ̨��Keil
���� �� �� Ƭ ����msp432P401R
���� �� �⡿msp432_driverlib_3_21_00_05
���� ����lv
* @@ ������ο� ����Ը�
* ���ض����Դ����
* 10.5(TimerA3_CH1:servo3)   5.7(TimerA2_CH2:servo2)   5.6(TimerA2_CH1:servo1)
* ���ռ�ձȷ�Χ5%-12.5%  ��������ռ�ձ�ֵrange 500 - 2500
* �汾 v1.0
* ʱ�� 2022��12��27��16:39:03
-------------------------------------------------------------------------------------------------------*/
#include "main.h"

/// @brief �����ʼ��
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
        PWMConfig.dutyCycle = 1000;              //��ʼռ�ձ�ֵΪ1000
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

/// @brief ���ö����ռ�ձ�
/// @param Servox ����� servo1  servo2  servo3  
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