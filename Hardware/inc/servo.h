/*-----------------------------------------------------------------------------------------------------
【平 台】Keil
【适 用 单 片 机】msp432P401R
【底 层 库】msp432_driverlib_3_21_00_05
【开 发】lv
* @@ 库仅供参考 后果自负
* 板载舵机资源介绍
* 
* 
* 版本 v1.0
* 时间 2022年12月27日16:39:03
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