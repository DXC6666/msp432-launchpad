/*-----------------------------------------------------------------------------------------------------
【平 台】Keil
【适 用 单 片 机】msp432P401R
【底 层 库】msp432_driverlib_3_21_00_05
【开 发】lv
* @@ 库仅供参考 后果自负
* 板载定时器A资源介绍
* 定时器A模块有个四个定时器 A0 A1 A2 A3  每个定时器有两个中断向量 0 和 N
* 
*
* 对于电机应用，功率越大，PWM频率越低，最低有500Hz或者1KHz的，在兆瓦级的应用中。
* 普通中小功率的，5K到20K常见，功率越低，电压等级越低，你所能使用的PWM频率越高。因为低压的MOSFET开关频率可以做到很高，而高压的IGBT却很难快速开关。普通的马达，10K到20K，都没问题。我们做KW级主变频器，开关频率10K。
* https://blog.csdn.net/meimiaorenshengqq/article/details/119177385 电机pwm频率选择参考
* 版本 v1.0
* 时间 2022年12月27日16:39:03
-------------------------------------------------------------------------------------------------------*/
#include "main.h"

/// @brief 定时器A中断初始化
/// @param TimeAx 选择定时器TimeA0 TimeA1 TimeA2 TimeA3
/// @param TIMER_PERIOD 自动重装载值 最大值65535 单位us         eg.TimerA_INT_Init(TimeA0, 10000) 定时器A0 10ms进入一次中断
void TimerA_INT_Init(TimeAx TimeAx, uint32_t TIMER_PERIOD)
{
		const Timer_A_UpModeConfig upConfig =
	{
					TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source 
					TIMER_A_CLOCKSOURCE_DIVIDER_48,         // SMCLK/48 = 1MHz 1/1000000 = 0.000001s = 0.001ms = 1us
					TIMER_PERIOD,                           // 类似stm32自动重装载值ARR  这里叫CCR0
					TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
					TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,    // Enable CCR0 interrupt
					TIMER_A_DO_CLEAR                        // Clear value
	};

    switch (TimeAx)
    {
    case TimeA0:
        //配置定时器TIMER_A0
        Timer_A_configureUpMode(TIMER_A0_BASE,&upConfig);
        //Interrupt_enableSleepOnIsrExit();//退出中断进入低功耗模式 没必要
        //选择计数模式      增计数模式   所以需要在isr中清除计数值
        Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);    
        //清除捕获比较中断标志位
        Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
	    //开启定时器端口中断
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
    
    //开启总中断
	Interrupt_enableMaster();  


}


Timer_A_PWMConfig PWMConfig = {
        TIMER_A_CLOCKSOURCE_SMCLK,                  //时钟源
        TIMER_A_CLOCKSOURCE_DIVIDER_1,              //时钟分频 范围1-64
        4800 - 1,                                   //自动重装载值（ARR）   默认频率10KHz  所以最大占空比 48 000 000/10 000 = 4800
        TIMER_A_CAPTURECOMPARE_REGISTER_1,          //通道1 （注意引脚定义）
        TIMER_A_OUTPUTMODE_TOGGLE_SET,              //输出模式  模式6
        0                                           //这里是改变占空比的地方 默认0%
    };
/// @brief PWM生成初始化
/// @param TimeAx 选择定时器TimeA0 TimeA1 TimeA2 TimeA3
/// @param TimerAx_CHx 选择通道TimerAx_CH0 TimerAx_CH1 TimerAx_CH2 TimerAx_CH3 TimerAx_CH4
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
        
        Timer_A_generatePWM(TIMER_A0_BASE, &PWMConfig); /* 初始化比较寄存器以产生 PWM */
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