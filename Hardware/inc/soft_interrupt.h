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
#ifndef __SOFT_INTERRUPT_H__
#define __SOFT_INTERRUPT_H__



void SOFT_Pending(uint32_t interruptNumber);
void SOFT_Unpending(uint32_t interruptNumber);
#endif
