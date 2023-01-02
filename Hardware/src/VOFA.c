/*-----------------------------------------------------------------------------------------------------
��ƽ ̨��Keil
���� �� �� Ƭ ����msp432P401R
���� �� �⡿msp432_driverlib_3_21_00_05
���� ����lv
* @@ ������ο� ����Ը�
* VOFA+��λ������
* ֧������Э��
* 	    RawData		:Э�������ڲ���Ҫ�������ݣ������鿴�ֽ��������󡣡�����ֱ�ӵ���������ʹ�á�
*		FireWater	:��Э����CSV�����ַ�������ֱ�ۼ�࣬�����printf�򵥡��������ַ����������ĸ����������Դ����������λ��������λ�������������ͨ���������ࡢ����Ƶ�ʲ��ߵ�ʱ��ʹ�á�
*		JustFloat	:��Э����С�˸���������ʽ���ֽ���Э�飬��ʮ�����Ƹ��㴫�䣬��ʡ������Э��ǳ��ʺ�����ͨ�������ࡢ����Ƶ�ʸߵ�ʱ��
* ���ط�ʽ �� https://www.vofa.plus/
* �汾 v1.0
* ʱ�� 2022��12��27��16:39:03
-------------------------------------------------------------------------------------------------------*/


#include "main.h"
Frame DataFrame;



/// @brief VOFA+��λ���������ݺ���  Э��JustFloat  ֻд�����֧����ͨ��  ��ʹ�õ�ͨ����0
/// @param ch0 
/// @param ch1 
/// @param ch2 
/// @param ch3 
/// @param UARTx UART0 UART1 UART2 UART3 ��Ҫ��ʼ����Ӧ����
void VOFA_TxData(float ch0, float ch1, float ch2, float ch3, UARTx UART)
{
        DataFrame.fdata[0] = ch0 ;
        DataFrame.fdata[1] = ch1 ;
        DataFrame.fdata[2] = ch2 ;
        DataFrame.fdata[3] = ch3 ;
        memcpy(DataFrame.TxData, (uint8_t *)DataFrame.fdata, sizeof(DataFrame.fdata));//ͨ��������������������   float -> char  
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

/// @brief VOFA+��λ���������ݺ���  Э��FireWater  ֻд�����֧����ͨ��  ��ʹ�õ�ͨ����0  ��ֻ����UART0
/// @param ch0 
/// @param ch1 
/// @param ch2 
/// @param ch3 
void VOFA_TxData_FireWater(float ch0, float ch1, float ch2, float ch3)
{
    printf(" %.2f , %.2f, %.2f, %.2f\n", ch0, ch1, ch2, ch3);
}