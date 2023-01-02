/*-----------------------------------------------------------------------------------------------------
【平 台】Keil
【适 用 单 片 机】msp432P401R
【底 层 库】msp432_driverlib_3_21_00_05
【开 发】lv
* @@ 库仅供参考 后果自负
* 板载EXTI资源介绍
* S1      :   P1.1
* S2      :   P1.4
* 版本 v1.0
* 时间 2022年12月27日16:39:03
-------------------------------------------------------------------------------------------------------*/

#include "main.h"

void key_Init(void)
{
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);  //必须配置上拉电阻
    EXTI_Init(GPIO_PORT_P1, GPIO_PIN1, falling);
    EXTI_Init(GPIO_PORT_P1, GPIO_PIN4, falling);
}