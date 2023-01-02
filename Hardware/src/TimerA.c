/*-----------------------------------------------------------------------------------------------------
��ƽ ̨��Keil
���� �� �� Ƭ ����msp432P401R
���� �� �⡿msp432_driverlib_3_21_00_05
���� ����lv
* @@ ������ο� ����Ը�
* ���ض�ʱ��A��Դ����
* ��ʱ��Aģ���и��ĸ���ʱ�� A0 A1 A2 A3  ÿ����ʱ���������ж����� 0 �� N
* 
*
* ���ڵ��Ӧ�ã�����Խ��PWMƵ��Խ�ͣ������500Hz����1KHz�ģ������߼���Ӧ���С�
* ��ͨ��С���ʵģ�5K��20K����������Խ�ͣ���ѹ�ȼ�Խ�ͣ�������ʹ�õ�PWMƵ��Խ�ߡ���Ϊ��ѹ��MOSFET����Ƶ�ʿ��������ܸߣ�����ѹ��IGBTȴ���ѿ��ٿ��ء���ͨ����10K��20K����û���⡣������KW������Ƶ��������Ƶ��10K��
* https://blog.csdn.net/meimiaorenshengqq/article/details/119177385 ���pwmƵ��ѡ��ο�
* �汾 v1.0
* ʱ�� 2022��12��27��16:39:03
-------------------------------------------------------------------------------------------------------*/
#include "main.h"

/// @brief ��ʱ��A�жϳ�ʼ��
/// @param TimeAx ѡ��ʱ��TimeA0 TimeA1 TimeA2 TimeA3
/// @param TIMER_PERIOD �Զ���װ��ֵ ���ֵ65535 ��λus         eg.TimerA_INT_Init(TimeA0, 10000) ��ʱ��A0 10ms����һ���ж�
void TimerA_INT_Init(TimeAx TimeAx, uint32_t TIMER_PERIOD)
{
		const Timer_A_UpModeConfig upConfig =
	{
					TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source 
					TIMER_A_CLOCKSOURCE_DIVIDER_48,         // SMCLK/48 = 1MHz 1/1000000 = 0.000001s = 0.001ms = 1us
					TIMER_PERIOD,                           // ����stm32�Զ���װ��ֵARR  �����CCR0
					TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
					TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,    // Enable CCR0 interrupt
					TIMER_A_DO_CLEAR                        // Clear value
	};

    switch (TimeAx)
    {
    case TimeA0:
        //���ö�ʱ��TIMER_A0
        Timer_A_configureUpMode(TIMER_A0_BASE,&upConfig);
        //Interrupt_enableSleepOnIsrExit();//�˳��жϽ���͹���ģʽ û��Ҫ
        //ѡ�����ģʽ      ������ģʽ   ������Ҫ��isr���������ֵ
        Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);    
        //�������Ƚ��жϱ�־λ
        Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
	    //������ʱ���˿��ж�
        Interrupt_enableInterrupt(INT_TA0_0);
        break;
    case TimeA1:
        Timer_A_configureUpMode(TIMER_A1_BASE,&upConfig);
        Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);    
        Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1);
        Interrupt_enableInterrupt(INT_TA1_0);
        break;
    case TimeA2:
        Timer_A_configureUpMode(TIMER_A2_BASE,&upConfig);
        Timer_A_startCounter(TIMER_A2_BASE, TIMER_A_UP_MODE);    
        Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2);
        Interrupt_enableInterrupt(INT_TA2_0);
        break; 
    case TimeA3:
        Timer_A_configureUpMode(TIMER_A3_BASE,&upConfig);
        Timer_A_startCounter(TIMER_A3_BASE, TIMER_A_UP_MODE);    
        Timer_A_clearCaptureCompareInterrupt(TIMER_A3_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3);
        Interrupt_enableInterrupt(INT_TA3_0);
        break; 
    
    }
    
    //�������ж�
	Interrupt_enableMaster();  


}


Timer_A_PWMConfig PWMConfig = {
        TIMER_A_CLOCKSOURCE_SMCLK,                  //ʱ��Դ
        TIMER_A_CLOCKSOURCE_DIVIDER_1,              //ʱ�ӷ�Ƶ ��Χ1-64
        4800 - 1,                                   //�Զ���װ��ֵ��ARR��   Ĭ��Ƶ��10KHz  �������ռ�ձ� 48 000 000/10 000 = 4800
        TIMER_A_CAPTURECOMPARE_REGISTER_1,          //ͨ��1 ��ע�����Ŷ��壩
        TIMER_A_OUTPUTMODE_TOGGLE_SET,              //���ģʽ  ģʽ6
        0                                           //�����Ǹı�ռ�ձȵĵط� Ĭ��0%
    };
/// @brief PWM���ɳ�ʼ��
/// @param TimeAx ѡ��ʱ��TimeA0 TimeA1 TimeA2 TimeA3
/// @param TimerAx_CHx ѡ��ͨ��TimerAx_CH0 TimerAx_CH1 TimerAx_CH2 TimerAx_CH3 TimerAx_CH4
void TimerA_PWM_Init(TimeAx TimeAx, TimerAx_CHx TimerAx_CHx)
{
    
    switch (TimeAx)
    {
    case TimeA0:
        switch (TimerAx_CHx)
        {
        case TimerAx_CH0:
            GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P7, GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
            PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_0;
            break;
        case TimerAx_CH1:
            GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4, GPIO_PRIMARY_MODULE_FUNCTION); 
            PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
            break;
        case TimerAx_CH2:
            GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5, GPIO_PRIMARY_MODULE_FUNCTION); 
            PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;
            break;
        case TimerAx_CH3:
            GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);
            PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_3; 
            break;
        case TimerAx_CH4:
            GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION); 
            PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_4;
            break;        
        }
        
        Timer_A_generatePWM(TIMER_A0_BASE, &PWMConfig); /* ��ʼ���ȽϼĴ����Բ��� PWM */
        break;
    case TimeA1:
        switch (TimerAx_CHx)
        {
        case TimerAx_CH0:
            GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P8, GPIO_PIN0, GPIO_PRIMARY_MODULE_FUNCTION); 
            PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_0;
            break;
        case TimerAx_CH1:
            GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P7, GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION); 
            PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
            break;
        case TimerAx_CH2:
            GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P7, GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION); 
            PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;
            break;
        case TimerAx_CH3:
            GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P7, GPIO_PIN5, GPIO_PRIMARY_MODULE_FUNCTION); 
            PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_3;
            break;
        case TimerAx_CH4:
            GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P7, GPIO_PIN4, GPIO_PRIMARY_MODULE_FUNCTION); 
            PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_4;
            break;        
        }
        Timer_A_generatePWM(TIMER_A1_BASE, &PWMConfig);
        break;
    case TimeA2:
        switch (TimerAx_CHx)
        {
        case TimerAx_CH0:
            GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P8, GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION); 
            PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_0;
            break;
        case TimerAx_CH1:
            GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P5, GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION); 
            PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
            break;
        case TimerAx_CH2:
            GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P5, GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION); 
            PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;
            break;
        case TimerAx_CH3:
            GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P6, GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION); 
            PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_3;
            break;
        case TimerAx_CH4:
            GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P6, GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION); 
            PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_4;
            break;        
        }
        Timer_A_generatePWM(TIMER_A2_BASE, &PWMConfig);
        break;
    case TimeA3:
        switch (TimerAx_CHx)
        {
        case TimerAx_CH0:
            GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P10, GPIO_PIN4, GPIO_PRIMARY_MODULE_FUNCTION); 
            PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_0;
            break;
        case TimerAx_CH1:
            GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P10, GPIO_PIN5, GPIO_PRIMARY_MODULE_FUNCTION); 
            PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
            break;
        case TimerAx_CH2:
            GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P8, GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION); 
            PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;
            break;
        case TimerAx_CH3:
            GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P9, GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION); 
            PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_3;
            break;
        case TimerAx_CH4:
            GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P9, GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
            PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_4; 
            break;        
        }
        Timer_A_generatePWM(TIMER_A3_BASE, &PWMConfig);
        break;

    }

}