/*-----------------------------------------------------------------------------------------------------
【平 台】Keil
【适 用 单 片 机】msp432P401R
【底 层 库】msp432_driverlib_3_21_00_05
【开 发】lv
* @@ 库仅供参考 后果自负
* 板载sys资源介绍
* 
* 
* 版本 v1.0
* 时间 2022年12月27日16:39:03
-------------------------------------------------------------------------------------------------------*/

#include "main.h"

/*************************************************
* 函 数 名:DCO_set
* 功 能:设置DCO频率
* 参 数:DCO_FRE:DCO_FRE为DCO可选频率在exinsystem.h中列出
* 注意事项:无
*************************************************/
void DCO_set(DOC_FRE_enum DCO_FRE)
{
	CS->CTL0 = 0;
	switch(DCO_FRE)
	{
		case(DCO_1_5M): CS->CTL0 = CS_CTL0_DCORSEL_0; break;//1.5Mhz
		case(DCO_3_0M): CS->CTL0 = CS_CTL0_DCORSEL_1; break;//3Mhz
		case(DCO_6_0M): CS->CTL0 = CS_CTL0_DCORSEL_2; break;//6Mhz
		case(DCO_12_0M): CS->CTL0 = CS_CTL0_DCORSEL_3; break;//12Mhz
		case(DCO_24_0M): CS->CTL0 = CS_CTL0_DCORSEL_4; break;//24Mhz
		case(DCO_48_0M): CS->CTL0 = CS_CTL0_DCORSEL_5; break;//48Mhz
		default:CS->CTL0 = CS_CTL0_DCORSEL_1; break;//3Mhz
	}
}

/*************************************************
* 函 数 名:MCLK_set
* 功 能:设置MCLK
* 参 数:
* CLK_source:时钟源列举，在exinsystem.h中列出
* CLK_DIV:为可选分频,在exinsystem.h中列出
* 注意事项:无
*************************************************/
void MCLK_set(CLK_source_enum CLK_source,CLK_DIV_enum CLK_DIV)
{
	CS->CTL1 = CS->CTL1 & ~(CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK);//棣栧厛娓呴浂MCLK鏃堕挓婧愯?剧疆浣嶅拰MCLK鍒嗛?戣?剧疆浣?
	switch(CLK_source)//杩涜?孧CLK鏃堕挓婧愮殑璁剧疆
	{
		case(LFXTCLK): CS->CTL1 |= CS_CTL1_SELM__LFXTCLK; break;
		case(VLOCLK): CS->CTL1 |= CS_CTL1_SELM__VLOCLK; break;
		case(REFOCLK): CS->CTL1 |= CS_CTL1_SELM__REFOCLK; break;
		case(DCOCLK): CS->CTL1 |= CS_CTL1_SELM__DCOCLK; break;
		case(MODOSC): CS->CTL1 |= CS_CTL1_SELM__MODOSC; break;
		case(HFXTCLK): CS->CTL1 |= CS_CTL1_SELM__HFXTCLK; break;
		default: CS->CTL1 |= CS_CTL1_SELM__DCOCLK; break;
	}
	switch(CLK_DIV)//杩涜?孧CLK鏃堕挓婧愮殑璁剧疆
	{
		case(CLK_DIV1): CS->CTL1 |= CS_CTL1_DIVM__1; break;
		case(CLK_DIV2): CS->CTL1 |= CS_CTL1_DIVM__2; break;
		case(CLK_DIV4): CS->CTL1 |= CS_CTL1_DIVM__4; break;
		case(CLK_DIV8): CS->CTL1 |= CS_CTL1_DIVM__8; break;
		case(CLK_DIV16): CS->CTL1 |= CS_CTL1_DIVM__16; break;
		case(CLK_DIV32): CS->CTL1 |= CS_CTL1_DIVM__32; break;
		case(CLK_DIV64): CS->CTL1 |= CS_CTL1_DIVM__64; break;
		case(CLK_DIV128): CS->CTL1 |= CS_CTL1_DIVM__128; break;
		default: CS->CTL1 |= CS_CTL1_DIVM__1; break;
	}
}



/*************************************************
* 函 数 名:Clock_get
* 功 能:获得时钟信号频率
* 参 数:
* SysClock_Handle:时钟信号列举，在sys.h中列出
* 注意事项:无
*************************************************/
void Clock_get(SysClkStruct *SysClock_Handle)
{
	SysClock_Handle->ACLK = CS_getACLK();
	SysClock_Handle->MCLK = CS_getMCLK();
	SysClock_Handle->HSMCLK = CS_getHSMCLK();
	SysClock_Handle->SMCLK = CS_getSMCLK();
	SysClock_Handle->BCLK = CS_getBCLK();
	
	
}




/// @brief 使用外部晶振 达到48MHz
/// @param  
void SysInit(void)
{
	//High:48MHz  Low:32768Hz
	//MCLK=48MHz  SMCLK=48MHz
    WDTCTL = WDTPW | WDTHOLD; // 停用看门狗

    /* 第一步需要配置我们的时钟引脚，这里的高速时钟使用的是外部晶振*/
    //低速时钟初始化比较慢
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ, GPIO_PIN3 | GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION); //High
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ, GPIO_PIN0 | GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION); //Low
    CS_setExternalClockSourceFrequency(32768, 48000000);

    /* Starting HFXT in non-bypass mode without a timeout. Before we start
     * we have to change VCORE to 1 to support the 48MHz frequency */
    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);

    /* 更改闪存控制器使用的等待状态数用于读取操作。
    当改变时钟的频率范围时，必须使用此函数以允许可读闪存
    通俗来讲就是CPU跑太快了，Flash跟不上，让CPU等等它 */
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 1);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 1);

    CS_startHFXT(false);          //这是晶体 需要驱动
    CS_startLFXT(CS_LFXT_DRIVE3); //驱动等级3

    MAP_CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);  //MCLK    48MHz   16分频时，滴答延时可达到最长
    MAP_CS_initClockSignal(CS_SMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1); //SMCLK   48MHz
	CS_initClockSignal(CS_HSMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);	 //HSMCLK  48MHz
    CS_initClockSignal(CS_ACLK	, CS_LFXTCLK_SELECT, CS_CLOCK_DIVIDER_1); 	 //ACLK	   32768Hz	
	CS_initClockSignal(CS_BCLK	, CS_LFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);	 //BCLK	   32768Hz
	
	// CS_initClockSignal(CS_ACLK	, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1); 	 //ACLK		这是不用外部低俗晶振  时钟源为CS_REFOCLK_SELECT
	// CS_initClockSignal(CS_BCLK	, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);	 //BCLK
}
