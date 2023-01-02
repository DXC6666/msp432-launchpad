/*-----------------------------------------------------------------------------------------------------
��ƽ ̨��Keil
���� �� �� Ƭ ����msp432P401R
���� �� �⡿msp432_driverlib_3_21_00_05
���� ����lv
* @@ ������ο� ����Ը�
* ���ض�ʱ��A��Դ����
* 
* 
* �汾 v1.0
* ʱ�� 2022��12��27��16:39:03
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