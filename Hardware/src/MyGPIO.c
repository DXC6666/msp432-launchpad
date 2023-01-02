/*-----------------------------------------------------------------------------------------------------
【平 台】Keil
【适 用 单 片 机】msp432P401R
【底 层 库】msp432_driverlib_3_21_00_05
【开 发】lv
* @@ 库仅供参考 后果自负
* 板载GPIO资源介绍
* 
* 
* 版本 v1.0
* 时间 2022年12月27日16:39:03
-------------------------------------------------------------------------------------------------------*/
#include "main.h"

/// @brief gpio设置输入电平
/// @param selectedPort 端口号
/// @param selectedPins pin号
/// @param BitValue  0 or 1
void GPIO_WriteBit(uint_fast8_t selectedPort, uint_fast16_t selectedPins, bool BitValue)
{
    if(BitValue == 1)
    GPIO_setOutputHighOnPin(selectedPort, selectedPins);
    else
    GPIO_setOutputLowOnPin(selectedPort, selectedPins);
}