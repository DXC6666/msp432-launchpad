/*-----------------------------------------------------------------------------------------------------
��ƽ ̨��Keil
���� �� �� Ƭ ����msp432P401R
���� �� �⡿msp432_driverlib_3_21_00_05
���� ����lv
* @@ ������ο� ����Ը�
* ����GPIO��Դ����
* 
* 
* �汾 v1.0
* ʱ�� 2022��12��27��16:39:03
-------------------------------------------------------------------------------------------------------*/
#include "main.h"

/// @brief gpio���������ƽ
/// @param selectedPort �˿ں�
/// @param selectedPins pin��
/// @param BitValue  0 or 1
void GPIO_WriteBit(uint_fast8_t selectedPort, uint_fast16_t selectedPins, bool BitValue)
{
    if(BitValue == 1)
    GPIO_setOutputHighOnPin(selectedPort, selectedPins);
    else
    GPIO_setOutputLowOnPin(selectedPort, selectedPins);
}