/*-----------------------------------------------------------------------------------------------------
��ƽ ̨��Keil
���� �� �� Ƭ ����msp432P401R
���� �� �⡿msp432_driverlib_3_21_00_05
���� ����lv
* @@ ������ο� ����Ը�
* ����EXTI��Դ����
* port1-6
* �汾 v1.0
* ʱ�� 2022��12��27��16:39:03
-------------------------------------------------------------------------------------------------------*/
#include "main.h"

/// @brief �ⲿ�жϳ�ʼ��
/// @param selectedPort port 1 - 6
/// @param selectedPins pin  0 - 7
/// @param mode         falling  or  rising
void EXTI_Init(uint_fast8_t selectedPort, uint_fast16_t selectedPins, EXIT_Mode mode)
{
    GPIO_clearInterruptFlag(selectedPort, selectedPins);    //����жϱ�־λ

    switch (mode)   //ѡ���жϴ�����ʽ
    {
    case rising:
        GPIO_interruptEdgeSelect(selectedPort, selectedPins, GPIO_LOW_TO_HIGH_TRANSITION);  
        break;
    case falling:
        GPIO_interruptEdgeSelect(selectedPort, selectedPins, GPIO_HIGH_TO_LOW_TRANSITION);
        break;
    }
    GPIO_enableInterrupt(selectedPort, selectedPins);   //ʹ�ܿ����ⲿ�ж�

    switch (selectedPort)   //ʹ�ܶ˿��ж� ѡ���жϺ�
    {
    case GPIO_PORT_P1:
        Interrupt_enableInterrupt(INT_PORT1);                        
        break;
    case GPIO_PORT_P2:
        Interrupt_enableInterrupt(INT_PORT2);  
        break;
    case GPIO_PORT_P3:
        Interrupt_enableInterrupt(INT_PORT3);  
        break;
    case GPIO_PORT_P4:
        Interrupt_enableInterrupt(INT_PORT4);  
        break;
    case GPIO_PORT_P5:
        Interrupt_enableInterrupt(INT_PORT5);  
        break;
    case GPIO_PORT_P6:
        Interrupt_enableInterrupt(INT_PORT6);  
        break;
    }
    
    Interrupt_enableMaster();   //ʹ�����ж�
    
}

