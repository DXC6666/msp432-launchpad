/*-----------------------------------------------------------------------------------------------------
��ƽ ̨��Keil
���� �� �� Ƭ ����msp432P401R
���� �� �⡿msp432_driverlib_3_21_00_05
���� ����lv
* @@ ������ο� ����Ը�
* ���ض����Դ����
* 
* 
* �汾 v1.0
* ʱ�� 2022��12��27��16:39:03
-------------------------------------------------------------------------------------------------------*/
#ifndef __SERVO_H__
#define __SERVO_H__



typedef enum
{
    Servo1,
    Servo2,
    Servo3,
}Servox;



void Servo_Init(Servox Servox);

void Servo_SetPWM(Servox Servox, uint_fast16_t compareValue);
#endif