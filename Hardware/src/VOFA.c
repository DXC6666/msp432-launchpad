/*-----------------------------------------------------------------------------------------------------
【平 台】Keil
【适 用 单 片 机】msp432P401R
【底 层 库】msp432_driverlib_3_21_00_05
【开 发】lv
* @@ 库仅供参考 后果自负
* VOFA+上位机介绍
* 支持三种协议
* 	    RawData		:协议适用于不需要解析数据，仅仅查看字节流的需求。【可以直接当串口助手使用】
*		FireWater	:本协议是CSV风格的字符串流，直观简洁，编程像printf简单。但由于字符串解析消耗更多的运算资源（无论在上位机还是下位机），建议仅在通道数量不多、发送频率不高的时候使用。
*		JustFloat	:本协议是小端浮点数组形式的字节流协议，纯十六进制浮点传输，节省带宽。此协议非常适合用在通道数量多、发送频率高的时候。
* 下载方式 ： https://www.vofa.plus/
* 版本 v1.0
* 时间 2022年12月27日16:39:03
-------------------------------------------------------------------------------------------------------*/


#include "main.h"
Frame DataFrame;



/// @brief VOFA+上位机发送数据函数  协议JustFloat  只写了最多支持四通道  不使用的通道置0
/// @param ch0 
/// @param ch1 
/// @param ch2 
/// @param ch3 
/// @param UARTx UART0 UART1 UART2 UART3 需要初始化对应串口
void VOFA_TxData(float ch0, float ch1, float ch2, float ch3, UARTx UART)
{
        DataFrame.fdata[0] = ch0 ;
        DataFrame.fdata[1] = ch1 ;
        DataFrame.fdata[2] = ch2 ;
        DataFrame.fdata[3] = ch3 ;
        memcpy(DataFrame.TxData, (uint8_t *)DataFrame.fdata, sizeof(DataFrame.fdata));//通过拷贝把数据重新整理   float -> char  
        DataFrame.TxData[16] = 0x00;
        DataFrame.TxData[17] = 0x00;
        DataFrame.TxData[18] = 0x80;
        DataFrame.TxData[19] = 0x7f;

        switch (UART)
        {
        case UART0:
            UART_transmitData(EUSCI_A0_BASE, DataFrame.TxData[0]);
            UART_transmitData(EUSCI_A0_BASE, DataFrame.TxData[1]);
            UART_transmitData(EUSCI_A0_BASE, DataFrame.TxData[2]);
            UART_transmitData(EUSCI_A0_BASE, DataFrame.TxData[3]);
            UART_transmitData(EUSCI_A0_BASE, DataFrame.TxData[4]);
            UART_transmitData(EUSCI_A0_BASE, DataFrame.TxData[5]);
            UART_transmitData(EUSCI_A0_BASE, DataFrame.TxData[6]);
            UART_transmitData(EUSCI_A0_BASE, DataFrame.TxData[7]);
            UART_transmitData(EUSCI_A0_BASE, DataFrame.TxData[8]);
            UART_transmitData(EUSCI_A0_BASE, DataFrame.TxData[9]);
            UART_transmitData(EUSCI_A0_BASE, DataFrame.TxData[10]);
            UART_transmitData(EUSCI_A0_BASE, DataFrame.TxData[11]);
            UART_transmitData(EUSCI_A0_BASE, DataFrame.TxData[12]);
            UART_transmitData(EUSCI_A0_BASE, DataFrame.TxData[13]);
            UART_transmitData(EUSCI_A0_BASE, DataFrame.TxData[14]);
            UART_transmitData(EUSCI_A0_BASE, DataFrame.TxData[15]);
            UART_transmitData(EUSCI_A0_BASE, DataFrame.TxData[16]);
            UART_transmitData(EUSCI_A0_BASE, DataFrame.TxData[17]);
            UART_transmitData(EUSCI_A0_BASE, DataFrame.TxData[18]);
            UART_transmitData(EUSCI_A0_BASE, DataFrame.TxData[19]);
            break;
        case UART1:
            UART_transmitData(EUSCI_A1_BASE, DataFrame.TxData[0]);
            UART_transmitData(EUSCI_A1_BASE, DataFrame.TxData[1]);
            UART_transmitData(EUSCI_A1_BASE, DataFrame.TxData[2]);
            UART_transmitData(EUSCI_A1_BASE, DataFrame.TxData[3]);
            UART_transmitData(EUSCI_A1_BASE, DataFrame.TxData[4]);
            UART_transmitData(EUSCI_A1_BASE, DataFrame.TxData[5]);
            UART_transmitData(EUSCI_A1_BASE, DataFrame.TxData[6]);
            UART_transmitData(EUSCI_A1_BASE, DataFrame.TxData[7]);
            UART_transmitData(EUSCI_A1_BASE, DataFrame.TxData[8]);
            UART_transmitData(EUSCI_A1_BASE, DataFrame.TxData[9]);
            UART_transmitData(EUSCI_A1_BASE, DataFrame.TxData[10]);
            UART_transmitData(EUSCI_A1_BASE, DataFrame.TxData[11]);
            UART_transmitData(EUSCI_A1_BASE, DataFrame.TxData[12]);
            UART_transmitData(EUSCI_A1_BASE, DataFrame.TxData[13]);
            UART_transmitData(EUSCI_A1_BASE, DataFrame.TxData[14]);
            UART_transmitData(EUSCI_A1_BASE, DataFrame.TxData[15]);
            UART_transmitData(EUSCI_A1_BASE, DataFrame.TxData[16]);
            UART_transmitData(EUSCI_A1_BASE, DataFrame.TxData[17]);
            UART_transmitData(EUSCI_A1_BASE, DataFrame.TxData[18]);
            UART_transmitData(EUSCI_A1_BASE, DataFrame.TxData[19]);
            break;
        case UART2:
            UART_transmitData(EUSCI_A2_BASE, DataFrame.TxData[0]);
            UART_transmitData(EUSCI_A2_BASE, DataFrame.TxData[1]);
            UART_transmitData(EUSCI_A2_BASE, DataFrame.TxData[2]);
            UART_transmitData(EUSCI_A2_BASE, DataFrame.TxData[3]);
            UART_transmitData(EUSCI_A2_BASE, DataFrame.TxData[4]);
            UART_transmitData(EUSCI_A2_BASE, DataFrame.TxData[5]);
            UART_transmitData(EUSCI_A2_BASE, DataFrame.TxData[6]);
            UART_transmitData(EUSCI_A2_BASE, DataFrame.TxData[7]);
            UART_transmitData(EUSCI_A2_BASE, DataFrame.TxData[8]);
            UART_transmitData(EUSCI_A2_BASE, DataFrame.TxData[9]);
            UART_transmitData(EUSCI_A2_BASE, DataFrame.TxData[10]);
            UART_transmitData(EUSCI_A2_BASE, DataFrame.TxData[11]);
            UART_transmitData(EUSCI_A2_BASE, DataFrame.TxData[12]);
            UART_transmitData(EUSCI_A2_BASE, DataFrame.TxData[13]);
            UART_transmitData(EUSCI_A2_BASE, DataFrame.TxData[14]);
            UART_transmitData(EUSCI_A2_BASE, DataFrame.TxData[15]);
            UART_transmitData(EUSCI_A2_BASE, DataFrame.TxData[16]);
            UART_transmitData(EUSCI_A2_BASE, DataFrame.TxData[17]);
            UART_transmitData(EUSCI_A2_BASE, DataFrame.TxData[18]);
            UART_transmitData(EUSCI_A2_BASE, DataFrame.TxData[19]);
            break;
        case UART3:
            UART_transmitData(EUSCI_A3_BASE, DataFrame.TxData[0]);
            UART_transmitData(EUSCI_A3_BASE, DataFrame.TxData[1]);
            UART_transmitData(EUSCI_A3_BASE, DataFrame.TxData[2]);
            UART_transmitData(EUSCI_A3_BASE, DataFrame.TxData[3]);
            UART_transmitData(EUSCI_A3_BASE, DataFrame.TxData[4]);
            UART_transmitData(EUSCI_A3_BASE, DataFrame.TxData[5]);
            UART_transmitData(EUSCI_A3_BASE, DataFrame.TxData[6]);
            UART_transmitData(EUSCI_A3_BASE, DataFrame.TxData[7]);
            UART_transmitData(EUSCI_A3_BASE, DataFrame.TxData[8]);
            UART_transmitData(EUSCI_A3_BASE, DataFrame.TxData[9]);
            UART_transmitData(EUSCI_A3_BASE, DataFrame.TxData[10]);
            UART_transmitData(EUSCI_A3_BASE, DataFrame.TxData[11]);
            UART_transmitData(EUSCI_A3_BASE, DataFrame.TxData[12]);
            UART_transmitData(EUSCI_A3_BASE, DataFrame.TxData[13]);
            UART_transmitData(EUSCI_A3_BASE, DataFrame.TxData[14]);
            UART_transmitData(EUSCI_A3_BASE, DataFrame.TxData[15]);
            UART_transmitData(EUSCI_A3_BASE, DataFrame.TxData[16]);
            UART_transmitData(EUSCI_A3_BASE, DataFrame.TxData[17]);
            UART_transmitData(EUSCI_A3_BASE, DataFrame.TxData[18]);
            UART_transmitData(EUSCI_A3_BASE, DataFrame.TxData[19]);
            break;        
        
        }
        
}

/// @brief VOFA+上位机发送数据函数  协议FireWater  只写了最多支持四通道  不使用的通道置0  这只能用UART0
/// @param ch0 
/// @param ch1 
/// @param ch2 
/// @param ch3 
void VOFA_TxData_FireWater(float ch0, float ch1, float ch2, float ch3)
{
    printf(" %.2f , %.2f, %.2f, %.2f\n", ch0, ch1, ch2, ch3);
}