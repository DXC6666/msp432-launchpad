/*-----------------------------------------------------------------------------------------------------
��ƽ ̨��Keil
���� �� �� Ƭ ����msp432P401R
���� �� �⡿msp432_driverlib_3_21_00_05
���� ����lv
* @@ ������ο� ����Ը�
* ������
* 
*
* �汾 v1.0
* ʱ�� 2022��12��27��16:39:03
-------------------------------------------------------------------------------------------------------*/
#include "main.h"

int main(void)
{
	char txt[30] = {0};
	double t = 0;
	
	//uint8_t priority_num = 0;
	SysClkStruct SysClock_Handle;
	//	int i = 0;
	//char UART_Buff[256] = {0};
	
	WDT_A_holdTimer();	//�رտ��Ź�
	SysInit();
	delay_init();
	led_Init();
	key_Init();
	uart_init(UART0);
	OLED_Init();
	OLED_SPI_Init();
	//TimerA_INT_Init(TimeA0, 65535);
	
	//Interrupt_enableMaster();
	while(1)
	{	
		
		Clock_get(&SysClock_Handle);
		printf("ACLK=%d\r\n",SysClock_Handle.ACLK);
		printf("BCLK=%d\r\n",SysClock_Handle.BCLK);
		printf("HSMCLK=%d\r\n",SysClock_Handle.HSMCLK);
		printf("MCLK=%d\r\n",SysClock_Handle.MCLK);
		printf("SMCLK=%d\r\n",SysClock_Handle.SMCLK);



		// SysClock_Handle.ACLK = CS_getACLK();
		// SysClock_Handle.MCLK = CS_getMCLK();
		// SysClock_Handle.HSMCLK = CS_getHSMCLK();
		// SysClock_Handle.SMCLK = CS_getSMCLK();
		// SysClock_Handle.BCLK = CS_getBCLK();
		//UART_transmitData(EUSCI_A0_BASE, UART_Buff); //��������
		//priority_num = Interrupt_getPriority(INT_PORT1);
		//printf("Hello World\r\n");
//		scanf("%s", UART_Buff);
		//OLED_ShowString(1, 1, "Hello World");
		// t+= 0.1;
		// VOFA_TxData(sin(t), sin(2*t), sin(3*t), sin(4*t), UART0 );
//		printf( "%.2f, %.2f\n", sin(t), sin(2*t));
		
		//printf( (char *)data);
		// printf(&data[0]);
		// UART_transmitData(EUSCI_A0_BASE, data[0]);
		// UART_transmitData(EUSCI_A0_BASE, data[1]);

		// delay_ms(100);
		// sprintf(txt, "mydata=%.2f", UART_Buff);
		// OLED_SPI_ShowString(10, 6, (uint8_t *)txt);
		
	}
	
}