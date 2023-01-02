/*-----------------------------------------------------------------------------------------------------
��ƽ ̨��Keil
���� �� �� Ƭ ����msp432P401R
���� �� �⡿msp432_driverlib_3_21_00_05
���� ����lv
* @@ ������ο� ����Ը�
* ����led��Դ����
* LED1      :   P1.0
* RGBLED2   :   RED P2.0   GREEN P2.1  BLUE P2.2
* �汾 v1.0
* ʱ�� 2022��12��27��16:39:03
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