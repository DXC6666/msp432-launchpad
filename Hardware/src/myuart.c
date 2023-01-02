/*-----------------------------------------------------------------------------------------------------
��ƽ ̨��Keil
���� �� �� Ƭ ����msp432P401R
���� �� �⡿msp432_driverlib_3_21_00_05
���� ����lv
* @@ ������ο� ����Ը�
* ����UART��Դ����
* UART0 :   RXD:P1.2   TXD:P1.3     �����ŵ�������
* UART1 :   RXD:P2.2   TXD:P2.3 
* UART2 :   RXD:P3.2   TXD:P3.3 
* UART3 :   RXD:P9.6   TXD:P9.7 
* http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html ����baudRate�ٷ�����
* �汾 v1.0
* ʱ�� 2022��12��27��16:39:03
-------------------------------------------------------------------------------------------------------*/

#include "main.h"


/// @brief ���ڳ�ʼ�� baudRate = 115200
/// @param UARTx UART0 UART1 UART2 UART3
void uart_init(UARTx UARTx)
{
    //2.���ô��ڽṹ��
    const eUSCI_UART_Config uartConfig =
        {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,                // SMCLK Clock Source
            26,                                            // BRDIV = 26
            0,                                             // UCxBRF = 0
            111,                                           // UCxBRS = 111
            EUSCI_A_UART_NO_PARITY,                        // No Parity
            EUSCI_A_UART_LSB_FIRST,                        // MSB First
            EUSCI_A_UART_ONE_STOP_BIT,                     // One stop bit
            EUSCI_A_UART_MODE,                             // UART mode
            EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION, // Oversampling
        };

 switch (UARTx)
    {
    case UART0:
        //1.����GPIO����
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION); // Ϊʲôֻ������Ϊ���뷽��   Ϊʲô�ǵ�һ����
        //3.��ʼ������
        UART_initModule(EUSCI_A0_BASE, &uartConfig);
        //4.��������ģ��
        UART_enableModule(EUSCI_A0_BASE);
        //5.������������ж�
        UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
        //6.�������ڶ˿��ж�
        Interrupt_enableInterrupt(INT_EUSCIA0);
        break;
    case UART1:
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION); 
        UART_initModule(EUSCI_A1_BASE, &uartConfig);
        UART_enableModule(EUSCI_A1_BASE);
        UART_enableInterrupt(EUSCI_A1_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
        Interrupt_enableInterrupt(INT_EUSCIA1);
        break;
    case UART2:
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION); 
        UART_initModule(EUSCI_A2_BASE, &uartConfig);
        UART_enableModule(EUSCI_A2_BASE);
        UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
        Interrupt_enableInterrupt(INT_EUSCIA2);
        break;
    case UART3:
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P9, GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION); 
        UART_initModule(EUSCI_A3_BASE, &uartConfig);
        UART_enableModule(EUSCI_A3_BASE);
        UART_enableInterrupt(EUSCI_A3_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
        Interrupt_enableInterrupt(INT_EUSCIA3);
        break;    
    }
    //7.�������ж�
    Interrupt_enableMaster();
    
}

//��׼������������Խ�
//ʹ��΢�� ��ȥ��ѡħ������� Use MicroLIB
//printf�ض���    
int fputc(int ch,FILE *f)
{
    UART_transmitData(EUSCI_A0_BASE,ch & 0xFF);
    return ch;
}
//scanf�ض���
int fgetc(FILE *f)
{
  while (EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG !=
         UART_getInterruptStatus(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG));
    
  return UART_receiveData(EUSCI_A0_BASE);
}