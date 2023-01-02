/*-----------------------------------------------------------------------------------------------------
【平 台】Keil
【适 用 单 片 机】msp432P401R
【底 层 库】msp432_driverlib_3_21_00_05
【开 发】lv
* @@ 库仅供参考 后果自负
* VOFA上位机介绍
* 支持三种协议
* 	    RawData		:协议适用于不需要解析数据，仅仅查看字节流的需求。【可以直接当串口助手使用】
*		FireWater	:本协议是CSV风格的字符串流，直观简洁，编程像printf简单。但由于字符串解析消耗更多的运算资源（无论在上位机还是下位机），建议仅在通道数量不多、发送频率不高的时候使用。
*		JustFloat	:本协议是小端浮点数组形式的字节流协议，纯十六进制浮点传输，节省带宽。此协议非常适合用在通道数量多、发送频率高的时候。
* 下载方式 ： https://www.vofa.plus/
* 版本 v1.0
* 时间 2022年12月27日16:39:03
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