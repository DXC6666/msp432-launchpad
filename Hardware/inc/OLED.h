/*-----------------------------------------------------------------------------------------------------
��ƽ ̨��Keil
���� �� �� Ƭ ����msp432P401R
���� �� �⡿msp432_driverlib_3_21_00_05
���� ����lv
* @@ ������ο� ����Ը�
* OLED  IIC��Դ����
* SCL      :   P3.6
* SDA      :   P3.7
* �汾 v1.0
* ʱ�� 2022��12��27��16:39:03
-------------------------------------------------------------------------------------------------------*/
#ifndef __OLED_H__
#define __OLED_H__


//oled����128*64  �ַ��ߴ�8*16
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
