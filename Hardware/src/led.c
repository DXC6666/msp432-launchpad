/*-----------------------------------------------------------------------------------------------------
【平 台】Keil
【适 用 单 片 机】msp432P401R
【底 层 库】msp432_driverlib_3_21_00_05
【开 发】lv
* @@ 库仅供参考 后果自负
* 板载led资源介绍
* LED1      :   P1.0
* RGBLED2   :   RED P2.0   GREEN P2.1  BLUE P2.2
* 版本 v1.0
* 时间 2022年12月27日16:39:03
-------------------------------------------------------------------------------------------------------*/
#include "main.h"

void led_Init(void)
{
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);//led1

    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);//led2 rgb
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2);
    
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
}
void led_on(led_state_t led_state)
{
    switch (led_state)
    {
    case led1:
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        break;
    case led2_red:
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
        break;
    case led2_green:
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
        break;
    case led2_blue:
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
        break;        
    default:
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
        break;
    }
    
}

void led_toggle(led_state_t led_state)
{
    switch (led_state)
    {
    case led1:
        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
        break;
    case led2_red:
        GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN0);
        break;
    case led2_green:
        GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN1);
        break;
    case led2_blue:
        GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN2);
        break;        
    default:
        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
        GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN0);
        GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN1);
        GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN2);
        break;
    }

}