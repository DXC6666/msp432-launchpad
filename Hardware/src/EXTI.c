/*-----------------------------------------------------------------------------------------------------
【平 台】Keil
【适 用 单 片 机】msp432P401R
【底 层 库】msp432_driverlib_3_21_00_05
【开 发】lv
* @@ 库仅供参考 后果自负
* 板载EXTI资源介绍
* port1-6
* 版本 v1.0
* 时间 2022年12月27日16:39:03
-------------------------------------------------------------------------------------------------------*/
#include "main.h"

/// @brief 外部中断初始化
/// @param selectedPort port 1 - 6
/// @param selectedPins pin  0 - 7
/// @param mode         falling  or  rising
void EXTI_Init(uint_fast8_t selectedPort, uint_fast16_t selectedPins, EXIT_Mode mode)
{
    GPIO_clearInterruptFlag(selectedPort, selectedPins);    //清除中断标志位

    switch (mode)   //选择中断触发方式
    {
    case rising:
        GPIO_interruptEdgeSelect(selectedPort, selectedPins, GPIO_LOW_TO_HIGH_TRANSITION);  
        break;
    case falling:
        GPIO_interruptEdgeSelect(selectedPort, selectedPins, GPIO_HIGH_TO_LOW_TRANSITION);
        break;
    }
    GPIO_enableInterrupt(selectedPort, selectedPins);   //使能开启外部中断

    switch (selectedPort)   //使能端口中断 选择中断号
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
    
    Interrupt_enableMaster();   //使能总中断
    
}

