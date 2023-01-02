/*-----------------------------------------------------------------------------------------------------
【平 台】Keil
【适 用 单 片 机】msp432P401R
【底 层 库】msp432_driverlib_3_21_00_05
【开 发】lv
* @@ 库仅供参考 后果自负
* 板载UART资源介绍
* UART0 :   RXD:P1.2   TXD:P1.3     连接着调试器的
* UART1 :   RXD:P2.2   TXD:P2.3 
* UART2 :   RXD:P3.2   TXD:P3.3 
* UART3 :   RXD:P9.6   TXD:P9.7 
* http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html 计算baudRate官方工具
* 版本 v1.0
* 时间 2022年12月27日16:39:03
-------------------------------------------------------------------------------------------------------*/

#include "main.h"


/// @brief 串口初始化 baudRate = 115200
/// @param UARTx UART0 UART1 UART2 UART3
void uart_init(UARTx UARTx)
{
    //2.配置串口结构体
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
        //1.配置GPIO复用
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION); // 为什么只用配置为输入方向？   为什么是第一功能
        //3.初始化串口
        UART_initModule(EUSCI_A0_BASE, &uartConfig);
        //4.开启串口模块
        UART_enableModule(EUSCI_A0_BASE);
        //5.开启串口相关中断
        UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
        //6.开启串口端口中断
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
    //7.开启总中断
    Interrupt_enableMaster();
    
}

//标准输入输出函数对接
//使用微库 得去勾选魔术棒里的 Use MicroLIB
//printf重定向    
int fputc(int ch,FILE *f)
{
    UART_transmitData(EUSCI_A0_BASE,ch & 0xFF);
    return ch;
}
//scanf重定向
int fgetc(FILE *f)
{
  while (EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG !=
         UART_getInterruptStatus(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG));
    
  return UART_receiveData(EUSCI_A0_BASE);
}