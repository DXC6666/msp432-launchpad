/*-----------------------------------------------------------------------------------------------------
【平 台】Keil
【适 用 单 片 机】msp432P401R
【底 层 库】msp432_driverlib_3_21_00_05
【开 发】lv
* @@ 库仅供参考 后果自负
* 板载中断服务函数资源介绍
* 
* 
* 版本 v1.0
* 时间 2022年12月27日16:39:03
-------------------------------------------------------------------------------------------------------*/
#include "main.h"

/// @brief 外部中断服务函数1
/// @param  
void PORT1_IRQHandler(void)
{
    uint_fast16_t status;
	status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);  //获取中断状态  这个状态其实就是pin号
    GPIO_clearInterruptFlag(GPIO_PORT_P1, status);          //清除中断标志  要不然下次不会进入isr

    if(status & GPIO_PIN1)
    {
        ///////////////////////用户程序///////////////////////////////////////
        
        

        
        led_toggle(led1);
        //////////////////////用户程序///////////////////////////////////////
    } 

    if(status & GPIO_PIN4)
    {
        ///////////////////////用户程序///////////////////////////////////////

        

        led_toggle(led1);
        //////////////////////用户程序///////////////////////////////////////
    }
		
		
		
		
}


/// @brief UART0中断服务函数
/// @param  
void EUSCIA0_IRQHandler(void)
{
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A0_BASE);
    uint8_t  RXData;
    UART_clearInterruptFlag(EUSCI_A0_BASE, status);  //清除中断标志   可以省去  硬件会自动清除

    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
       
        ///////////////////////用户程序///////////////////////////////////////
        RXData = UART_receiveData(EUSCI_A0_BASE);
        
        UART_transmitData(EUSCI_A0_BASE, UART_receiveData(EUSCI_A0_BASE)); //发送接受的数据
        

        
        //////////////////////用户程序///////////////////////////////////////
        Interrupt_disableSleepOnIsrExit();  //Disables the processor to sleep when exiting an ISR.
    }

}

void TA0_0_IRQHandler(void)
{
    Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0); //清除捕获比较中断标志位
    Timer_A_clearTimer(TIMER_A0_BASE);//清除定时器计数
    ///////////////////////用户程序///////////////////////////////////////

        

    led_toggle(led1);
    //////////////////////用户程序///////////////////////////////////////
}