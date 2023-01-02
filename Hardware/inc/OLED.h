/*-----------------------------------------------------------------------------------------------------
【平 台】Keil
【适 用 单 片 机】msp432P401R
【底 层 库】msp432_driverlib_3_21_00_05
【开 发】lv
* @@ 库仅供参考 后果自负
* OLED  IIC资源介绍
* SCL      :   P3.6
* SDA      :   P3.7
* 版本 v1.0
* 时间 2022年12月27日16:39:03
-------------------------------------------------------------------------------------------------------*/
#ifndef __OLED_H__
#define __OLED_H__


//oled像素128*64  字符尺寸8*16
void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

void OLED_ShowChinese(uint8_t Line, uint8_t Column, uint8_t Hz );
void OLED_ShowPhoto(uint8_t Column, uint8_t Photo);
void OLED_ShowFloat(uint8_t Line, uint8_t Column, float Float, char *Char);
#endif
