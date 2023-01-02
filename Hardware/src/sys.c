/*-----------------------------------------------------------------------------------------------------
��ƽ ̨��Keil
���� �� �� Ƭ ����msp432P401R
���� �� �⡿msp432_driverlib_3_21_00_05
���� ����lv
* @@ ������ο� ����Ը�
* ����sys��Դ����
* 
* 
* �汾 v1.0
* ʱ�� 2022��12��27��16:39:03
-------------------------------------------------------------------------------------------------------*/

#include "main.h"

/*************************************************
* �� �� ��:DCO_set
* �� ��:����DCOƵ��
* �� ��:DCO_FRE:DCO_FREΪDCO��ѡƵ����exinsystem.h���г�
* ע������:��
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
* �� �� ��:MCLK_set
* �� ��:����MCLK
* �� ��:
* CLK_source:ʱ��Դ�о٣���exinsystem.h���г�
* CLK_DIV:Ϊ��ѡ��Ƶ,��exinsystem.h���г�
* ע������:��
*************************************************/
void MCLK_set(CLK_source_enum CLK_source,CLK_DIV_enum CLK_DIV)
{
	CS->CTL1 = CS->CTL1 & ~(CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK);//首先清零MCLK时钟源�?�置位和MCLK分�?��?�置�?
	switch(CLK_source)//进�?�MCLK时钟源的设置
	{
		case(LFXTCLK): CS->CTL1 |= CS_CTL1_SELM__LFXTCLK; break;
		case(VLOCLK): CS->CTL1 |= CS_CTL1_SELM__VLOCLK; break;
		case(REFOCLK): CS->CTL1 |= CS_CTL1_SELM__REFOCLK; break;
		case(DCOCLK): CS->CTL1 |= CS_CTL1_SELM__DCOCLK; break;
		case(MODOSC): CS->CTL1 |= CS_CTL1_SELM__MODOSC; break;
		case(HFXTCLK): CS->CTL1 |= CS_CTL1_SELM__HFXTCLK; break;
		default: CS->CTL1 |= CS_CTL1_SELM__DCOCLK; break;
	}
	switch(CLK_DIV)//进�?�MCLK时钟源的设置
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
* �� �� ��:Clock_get
* �� ��:���ʱ���ź�Ƶ��
* �� ��:
* SysClock_Handle:ʱ���ź��о٣���sys.h���г�
* ע������:��
*************************************************/
void Clock_get(SysClkStruct *SysClock_Handle)
{
	SysClock_Handle->ACLK = CS_getACLK();
	SysClock_Handle->MCLK = CS_getMCLK();
	SysClock_Handle->HSMCLK = CS_getHSMCLK();
	SysClock_Handle->SMCLK = CS_getSMCLK();
	SysClock_Handle->BCLK = CS_getBCLK();
	
	
}




/// @brief ʹ���ⲿ���� �ﵽ48MHz
/// @param  
void SysInit(void)
{
	//High:48MHz  Low:32768Hz
	//MCLK=48MHz  SMCLK=48MHz
    WDTCTL = WDTPW | WDTHOLD; // ͣ�ÿ��Ź�

    /* ��һ����Ҫ�������ǵ�ʱ�����ţ�����ĸ���ʱ��ʹ�õ����ⲿ����*/
    //����ʱ�ӳ�ʼ���Ƚ���
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ, GPIO_PIN3 | GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION); //High
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ, GPIO_PIN0 | GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION); //Low
    CS_setExternalClockSourceFrequency(32768, 48000000);

    /* Starting HFXT in non-bypass mode without a timeout. Before we start
     * we have to change VCORE to 1 to support the 48MHz frequency */
    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);

    /* �������������ʹ�õĵȴ�״̬�����ڶ�ȡ������
    ���ı�ʱ�ӵ�Ƶ�ʷ�Χʱ������ʹ�ô˺���������ɶ�����
    ͨ����������CPU��̫���ˣ�Flash�����ϣ���CPU�ȵ��� */
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 1);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 1);

    CS_startHFXT(false);          //���Ǿ��� ��Ҫ����
    CS_startLFXT(CS_LFXT_DRIVE3); //�����ȼ�3

    MAP_CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);  //MCLK    48MHz   16��Ƶʱ���δ���ʱ�ɴﵽ�
    MAP_CS_initClockSignal(CS_SMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1); //SMCLK   48MHz
	CS_initClockSignal(CS_HSMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);	 //HSMCLK  48MHz
    CS_initClockSignal(CS_ACLK	, CS_LFXTCLK_SELECT, CS_CLOCK_DIVIDER_1); 	 //ACLK	   32768Hz	
	CS_initClockSignal(CS_BCLK	, CS_LFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);	 //BCLK	   32768Hz
	
	// CS_initClockSignal(CS_ACLK	, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1); 	 //ACLK		���ǲ����ⲿ���׾���  ʱ��ԴΪCS_REFOCLK_SELECT
	// CS_initClockSignal(CS_BCLK	, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);	 //BCLK
}
