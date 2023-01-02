/*-----------------------------------------------------------------------------------------------------
【平 台】Keil
【适 用 单 片 机】msp432P401R
【底 层 库】msp432_driverlib_3_21_00_05
【开 发】lv
* @@ 库仅供参考 后果自负
* 板载软件挂起中断资源介绍
* 
* 
* 版本 v1.0
* 时间 2022年12月27日16:39:03
-------------------------------------------------------------------------------------------------------*/
#include "main.h"

/// @brief 使能软件挂起中断
/// @param interruptNumber  指定挂起中断的中断号
void SOFT_Pending(uint32_t interruptNumber)
{
	Interrupt_enableInterrupt(INT_PORT1);   
	Interrupt_pendInterrupt(interruptNumber);
	
}

/// @brief 失能软件挂起中断
/// @param interruptNumber  指定挂起中断的中断号
void SOFT_Unpending(uint32_t interruptNumber)
{
	Interrupt_unpendInterrupt(interruptNumber);
}
	

/// @brief 中断屏蔽  屏蔽掉大于等于priorityMask的中断会被屏蔽掉  为0时 关闭屏蔽
/// @param priorityMask 0 - 7  共八级可编程中断等级
void INT_Mask(uint8_t priorityMask)
{
	 Interrupt_setPriorityMask (priorityMask << 5);
}


/// @brief 设置中断的组优先级
/// @param interruptNumber 中断号
/// @param priority 等级 range 0 - 7
void INT_SetPriority(uint32_t interruptNumber, uint8_t priority)
{
	Interrupt_setPriority(interruptNumber, priority << 5);

}









