/*-----------------------------------------------------------------------------------------------------
��ƽ ̨��Keil
���� �� �� Ƭ ����msp432P401R
���� �� �⡿msp432_driverlib_3_21_00_05
���� ����lv
* @@ ������ο� ����Ը�
* �����жϷ�������Դ����
* 
* 
* �汾 v1.0
* ʱ�� 2022��12��27��16:39:03
-------------------------------------------------------------------------------------------------------*/
#include "main.h"

/// @brief �ⲿ�жϷ�����1
/// @param  
void PORT1_IRQHandler(void)
{
    uint_fast16_t status;
	status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);  //��ȡ�ж�״̬  ���״̬��ʵ����pin��
    GPIO_clearInterruptFlag(GPIO_PORT_P1, status);          //����жϱ�־  Ҫ��Ȼ�´β������isr

    if(status & GPIO_PIN1)
    {
        ///////////////////////�û�����///////////////////////////////////////
        
        

        
        led_toggle(led1);
        //////////////////////�û�����///////////////////////////////////////
    } 

    if(status & GPIO_PIN4)
    {
        ///////////////////////�û�����///////////////////////////////////////

        

        led_toggle(led1);
        //////////////////////�û�����///////////////////////////////////////
    }
		
		
		
		
}


/// @brief UART0�жϷ�����
/// @param  
void EUSCIA0_IRQHandler(void)
{
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A0_BASE);
    uint8_t  RXData;
    UART_clearInterruptFlag(EUSCI_A0_BASE, status);  //����жϱ�־   ����ʡȥ  Ӳ�����Զ����

    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
       
        ///////////////////////�û�����///////////////////////////////////////
        RXData = UART_receiveData(EUSCI_A0_BASE);
        
        UART_transmitData(EUSCI_A0_BASE, UART_receiveData(EUSCI_A0_BASE)); //���ͽ��ܵ�����
        

        
        //////////////////////�û�����///////////////////////////////////////
        Interrupt_disableSleepOnIsrExit();  //Disables the processor to sleep when exiting an ISR.
    }

}

void TA0_0_IRQHandler(void)
{
    Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0); //�������Ƚ��жϱ�־λ
    Timer_A_clearTimer(TIMER_A0_BASE);//�����ʱ������
    ///////////////////////�û�����///////////////////////////////////////

        

    led_toggle(led1);
    //////////////////////�û�����///////////////////////////////////////
}