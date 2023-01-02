/*-----------------------------------------------------------------------------------------------------
��ƽ ̨��Keil
���� �� �� Ƭ ����msp432P401R
���� �� �⡿msp432_driverlib_3_21_00_05
���� ����lv
* @@ ������ο� ����Ը�
* OLED  ģ��IIC��Դ����
* SCL      :   P3.6
* SDA      :   P3.7
* �汾 v1.0
* ʱ�� 2022��12��27��16:39:03
-------------------------------------------------------------------------------------------------------*/
#include "main.h"
#include "OLED_Font.h"  


/*��������*/
#define OLED_W_SCL(x)		GPIO_WriteBit(GPIO_PORT_P3, GPIO_PIN6, (x))
#define OLED_W_SDA(x)		GPIO_WriteBit(GPIO_PORT_P3, GPIO_PIN7, (x))

/*���ų�ʼ��*/
void OLED_I2C_Init(void)
{
   

	GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN6);
	GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN7);
	
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}

/**
  * @brief  I2C��ʼ
  * @param  ��
  * @retval ��
  */
void OLED_I2C_Start(void)
{
	OLED_W_SDA(1);
	OLED_W_SCL(1);
	OLED_W_SDA(0);
	OLED_W_SCL(0);
}

/**
  * @brief  I2Cֹͣ
  * @param  
  * @retval 
  */
void OLED_I2C_Stop(void)
{
	OLED_W_SDA(0);
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}

/**
  * @brief  I2C����һ���ֽ�
  * @param  Byte Ҫ���͵�һ���ֽ�
  * @retval ��
  */
void OLED_I2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		OLED_W_SDA(Byte & (0x80 >> i));
		OLED_W_SCL(1);
		OLED_W_SCL(0);
	}
	OLED_W_SCL(1);	//额�?的一�?��钟，不�?理应答信�?
	OLED_W_SCL(0);
}

/**
  * @brief  OLEDд����
  * @param  Command Ҫд�������
  * @retval ��
  */
void OLED_WriteCommand(uint8_t Command)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//�ӻ���ַ
	OLED_I2C_SendByte(0x00);		//д���� Co=0 D/C=0 000 000
	OLED_I2C_SendByte(Command); 
	OLED_I2C_Stop();
}

/**
  * @brief  OLEDд����
  * @param  Data Ҫд�������
  * @retval ��
  */
void OLED_WriteData(uint8_t Data)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//�ӻ���ַ
	OLED_I2C_SendByte(0x40);		//д���� Co=0 D/C=1 000 000
	OLED_I2C_SendByte(Data);
	OLED_I2C_Stop();
}

/**
  * @brief  OLED设置光标位置
  * @param  Y 以左上�?为原点，向下方向的坐标，范围�?0~7
  * @param  X 以左上�?为原点，向右方向的坐标，范围�?0~127
  * @retval ��
  */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
	OLED_WriteCommand(0xB0 | Y);					//设置页位�?           列地址高四位的�?4位固定是0b0001,低四位的�?4位固定是0b0000
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//设置列位�?��4�?
	OLED_WriteCommand((X & 0x0F));					//设置列位�?��4�?
}

/**
  * @brief  OLED清屏
  * @param  ��
  * @retval ��
  */
void OLED_Clear(void)
{  
	uint8_t i, j;
	for (j = 0; j < 8; j++)
	{
		OLED_SetCursor(j, 0);
		for(i = 0; i < 128; i++)
		{
			OLED_WriteData(0x00);
		}
	}
}

/**
  * @brief  OLED显示一�?���?
  * @param  Line 行位�?��范围�?1~4
  * @param  Column 列位�?��范围�?1~16
  * @param  Char 要显示的一�?��符，范围：ASCII�??字�?
  * @retval ��
  */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{      	
	uint8_t i;
	OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);		//设置光标位置在上半部�?
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Char - ' '][i]);			//显示上半部分内�?  空字�?scii�?32
	}
	OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);	//设置光标位置在下半部�?
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Char - ' '][i + 8]);		//显示下半部分内�?
	}
}

/**
  * @brief  OLED��ʾ�ַ���
  * @param  Line ��ʼ��λ�ã���Χ��1~4
  * @param  Column ��ʼ��λ�ã���Χ��1~16
  * @param  String Ҫ��ʾ���ַ�������Χ��ASCII�ɼ��ַ�
  * @retval ��
  */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)    //'\0'字�?串的结尾标志
	{
		OLED_ShowChar(Line, Column + i, String[i]);
	}
}

/**
  * @brief  OLED次方函数
  * @retval 返回值等于X的Y次方
  */
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y--)
	{
		Result *= X;
	}
	return Result;
}

/**
  * @brief  OLED显示数字（十进制，�?数）
  * @param  Line 起�?行位�?��范围�?1~4
  * @param  Column 起�?列位�?��范围�?1~16
  * @param  Number 要显示的数字，范围：0~4294967295
  * @param  Length 要显示数字的长度，范围：1~10
  * @retval ��
  */
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i, Number / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
  * @brief  OLED显示数字（十进制，带符号数）
  * @param  Line 起�?行位�?��范围�?1~4
  * @param  Column 起�?列位�?��范围�?1~16
  * @param  Number 要显示的数字，范围：-2147483648~2147483647
  * @param  Length 要显示数字的长度，范围：1~10
  * @retval ��
  */
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
{
	uint8_t i;
	uint32_t Number1;
	if (Number >= 0)
	{
		OLED_ShowChar(Line, Column, '+');
		Number1 = Number;
	}
	else
	{
		OLED_ShowChar(Line, Column, '-');
		Number1 = -Number;
	}
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i + 1, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
  * @brief  OLED显示数字（十�?��制，正数�?
  * @param  Line 起�?行位�?��范围�?1~4
  * @param  Column 起�?列位�?��范围�?1~16
  * @param  Number 要显示的数字，范围：0~0xFFFFFFFF
  * @param  Length 要显示数字的长度，范围：1~8
  * @retval ��
  */
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i, SingleNumber;
	for (i = 0; i < Length; i++)							
	{
		SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
		if (SingleNumber < 10)
		{
			OLED_ShowChar(Line, Column + i, SingleNumber + '0');
		}
		else
		{
			OLED_ShowChar(Line, Column + i, SingleNumber - 10 + 'A');
		}
	}
}

/**
  * @brief  OLED显示数字（二进制，�?数）
  * @param  Line 起�?行位�?��范围�?1~4
  * @param  Column 起�?列位�?��范围�?1~16
  * @param  Number 要显示的数字，范围：0~1111 1111 1111 1111
  * @param  Length 要显示数字的长度，范围：1~16
  * @retval ��
  */
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i, Number / OLED_Pow(2, Length - i - 1) % 2 + '0');
	}
}

/**
  * @brief  OLED��ʼ��
  * @param  ��
  * @retval ��
  */
void OLED_Init(void)
{
	uint32_t i, j;
	
	for (i = 0; i < 1000; i++)			//上电延时
	{
		for (j = 0; j < 1000; j++);
	}
	
	OLED_I2C_Init();			//�?��初�?�?
	
	OLED_WriteCommand(0xAE);	//关闭显示
	
	OLED_WriteCommand(0xD5);	//设置显示时钟分�?�?/�?��器�?�?
	OLED_WriteCommand(0x80);
	
	OLED_WriteCommand(0xA8);	//设置多路复用�?
	OLED_WriteCommand(0x3F);
	
	OLED_WriteCommand(0xD3);	//设置显示偏移
	OLED_WriteCommand(0x00);
	
	OLED_WriteCommand(0x40);	//设置显示开始�?
	
	OLED_WriteCommand(0xA1);	//设置左右方向�?0xA1正常 0xA0左右反置
	
	OLED_WriteCommand(0xC8);	//设置上下方向�?0xC8正常 0xC0上下反置

	OLED_WriteCommand(0xDA);	//设置COM引脚�?��配置
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);	//设置对比度控�?
	OLED_WriteCommand(0xCF);

	OLED_WriteCommand(0xD9);	//设置预充电周�?
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB);	//设置VCOMH取消选择级别
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4);	//设置整个显示打开/关闭

	OLED_WriteCommand(0xA6);	//设置正常/倒转显示

	OLED_WriteCommand(0x8D);	//设置充电�?
	OLED_WriteCommand(0x14);

	OLED_WriteCommand(0xAF);	//开�?���?
		
	OLED_Clear();				//OLED清屏
}
/*
	��ʾ����16*16
	����1-4 ����1-8

*/
void OLED_ShowChinese(uint8_t Line, uint8_t Column, uint8_t Hz )
{
	uint16_t i=8;
	OLED_SetCursor((Line-1)*2, (Column-1)*16);
	for(i=0;i<16;i++)
	{
		OLED_WriteData(Hzk[2*Hz][i]);
	}
	OLED_SetCursor((Line-1)*2+1, (Column-1)*16);
	for(i=0;i<16;i++)
	{
		OLED_WriteData(Hzk[2*Hz+1][i]);
	}
}
/*
	��ʾ64*64��BMPͼƬ
	Column:0-64
*/
void OLED_ShowPhoto(uint8_t Column, uint8_t Photo)
{
		uint16_t i=0;
	
		OLED_SetCursor(0, Column);
	for(i=0;i<64;i++)
	{
		OLED_WriteData(Photok[8*Photo][i]);
	}
		OLED_SetCursor(1, Column);
	for(i=0;i<64;i++)
	{
		OLED_WriteData(Photok[8*Photo+1][i]);
	}
		OLED_SetCursor(2, Column);
	for(i=0;i<64;i++)
	{
		OLED_WriteData(Photok[8*Photo+2][i]);
	}
		OLED_SetCursor(3, Column);
	for(i=0;i<64;i++)
	{
		OLED_WriteData(Photok[8*Photo+3][i]);
	}
		OLED_SetCursor(4, Column);
	for(i=0;i<64;i++)
	{
		OLED_WriteData(Photok[8*Photo+4][i]);
	}
		OLED_SetCursor(5, Column);
	for(i=0;i<64;i++)
	{
		OLED_WriteData(Photok[8*Photo+5][i]);
	}
		OLED_SetCursor(6, Column);
	for(i=0;i<64;i++)
	{
		OLED_WriteData(Photok[8*Photo+6][i]);
	}
		OLED_SetCursor(7, Column);
	for(i=0;i<64;i++)
	{
		OLED_WriteData(Photok[8*Photo+7][i]);
	}
}
/**
  * @brief  OLED万能显示
  * @param  uint8_t Line	：�? 1-4
  * @param  uint8_t Column	：列 1-16
  * @param  float Float		：�?显示的数
  * @param  char *Char		：显示的注释
  * @retval None
  */
void OLED_ShowFloat(uint8_t Line, uint8_t Column, float Float, char *Char)
{
	char txt[30];
	OLED_ShowString(Line, Column, Char);
	sprintf(txt,":%.1f ",Float);
	OLED_ShowString(Line, Column+strlen(Char),txt);
}