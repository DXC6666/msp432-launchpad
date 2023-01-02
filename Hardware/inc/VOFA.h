/*-----------------------------------------------------------------------------------------------------
��ƽ ̨��Keil
���� �� �� Ƭ ����msp432P401R
���� �� �⡿msp432_driverlib_3_21_00_05
���� ����lv
* @@ ������ο� ����Ը�
* VOFA��λ������
* ֧������Э��
* 	    RawData		:Э�������ڲ���Ҫ�������ݣ������鿴�ֽ��������󡣡�����ֱ�ӵ���������ʹ�á�
*		FireWater	:��Э����CSV�����ַ�������ֱ�ۼ�࣬�����printf�򵥡��������ַ����������ĸ����������Դ����������λ��������λ�������������ͨ���������ࡢ����Ƶ�ʲ��ߵ�ʱ��ʹ�á�
*		JustFloat	:��Э����С�˸���������ʽ���ֽ���Э�飬��ʮ�����Ƹ��㴫�䣬��ʡ������Э��ǳ��ʺ�����ͨ�������ࡢ����Ƶ�ʸߵ�ʱ��
* ���ط�ʽ �� https://www.vofa.plus/
* �汾 v1.0
* ʱ�� 2022��12��27��16:39:03
-------------------------------------------------------------------------------------------------------*/
#ifndef __VOFA_H__
#define __VOFA_H__






#define CH_COUNT 4
typedef struct  
{
    float fdata[CH_COUNT];
    uint8_t  tail[4];
    uint8_t  TxData[20];

}Frame;

extern Frame DataFrame;



void VOFA_TxData(float ch0, float ch1, float ch2, float ch3, UARTx UART);
void VOFA_TxData_FireWater(float ch0, float ch1, float ch2, float ch3);

#endif