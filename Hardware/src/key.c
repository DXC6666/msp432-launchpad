/*-----------------------------------------------------------------------------------------------------
��ƽ ̨��Keil
���� �� �� Ƭ ����msp432P401R
���� �� �⡿msp432_driverlib_3_21_00_05
���� ����lv
* @@ ������ο� ����Ը�
* ����EXTI��Դ����
* S1      :   P1.1
* S2      :   P1.4
* �汾 v1.0
* ʱ�� 2022��12��27��16:39:03
-------------------------------------------------------------------------------------------------------*/

#include "main.h"

void key_Init(void)
{
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);  //����������������
    EXTI_Init(GPIO_PORT_P1, GPIO_PIN1, falling);
    EXTI_Init(GPIO_PORT_P1, GPIO_PIN4, falling);
}