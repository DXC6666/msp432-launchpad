/*-----------------------------------------------------------------------------------------------------
【平 台】Keil
【适 用 单 片 机】msp432P401R
【底 层 库】msp432_driverlib_3_21_00_05
【开 发】lv
* @@ 库仅供参考 后果自负
* OLED  模拟IIC资源介绍
* SCL      :   P3.6
* SDA      :   P3.7
* 版本 v1.0
* 时间 2022年12月27日16:39:03
-------------------------------------------------------------------------------------------------------*/
#include "main.h"
#include "OLED_Font.h"  


/*引脚配置*/
#define OLED_W_SCL(x)		GPIO_WriteBit(GPIO_PORT_P3, GPIO_PIN6, (x))
#define OLED_W_SDA(x)		GPIO_WriteBit(GPIO_PORT_P3, GPIO_PIN7, (x))

/*引脚初始化*/
void OLED_I2C_Init(void)
{
   

	GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN6);
	GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN7);
	
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}

/**
  * @brief  I2C开始
  * @param  无
  * @retval 无
  */
void OLED_I2C_Start(void)
{
	OLED_W_SDA(1);
	OLED_W_SCL(1);
	OLED_W_SDA(0);
	OLED_W_SCL(0);
}

/**
  * @brief  I2C停止
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
  * @brief  I2C发送一个字节
  * @param  Byte 要发送的一个字节
  * @retval 无
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
	OLED_W_SCL(1);	//棰濆?鐨勪竴涓?椂閽燂紝涓嶅?鐞嗗簲绛斾俊鍙?
	OLED_W_SCL(0);
}

/**
  * @brief  OLED写命令
  * @param  Command 要写入的命令
  * @retval 无
  */
void OLED_WriteCommand(uint8_t Command)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//从机地址
	OLED_I2C_SendByte(0x00);		//写命令 Co=0 D/C=0 000 000
	OLED_I2C_SendByte(Command); 
	OLED_I2C_Stop();
}

/**
  * @brief  OLED写数据
  * @param  Data 要写入的数据
  * @retval 无
  */
void OLED_WriteData(uint8_t Data)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//从机地址
	OLED_I2C_SendByte(0x40);		//写数据 Co=0 D/C=1 000 000
	OLED_I2C_SendByte(Data);
	OLED_I2C_Stop();
}

/**
  * @brief  OLED璁剧疆鍏夋爣浣嶇疆
  * @param  Y 浠ュ乏涓婅?涓哄師鐐癸紝鍚戜笅鏂瑰悜鐨勫潗鏍囷紝鑼冨洿锛?0~7
  * @param  X 浠ュ乏涓婅?涓哄師鐐癸紝鍚戝彸鏂瑰悜鐨勫潗鏍囷紝鑼冨洿锛?0~127
  * @retval 无
  */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
	OLED_WriteCommand(0xB0 | Y);					//璁剧疆椤典綅缃?           鍒楀湴鍧?楂樺洓浣嶇殑鍓?4浣嶅浐瀹氭槸0b0001,浣庡洓浣嶇殑鍓?4浣嶅浐瀹氭槸0b0000
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//璁剧疆鍒椾綅缃?珮4浣?
	OLED_WriteCommand((X & 0x0F));					//璁剧疆鍒椾綅缃?綆4浣?
}

/**
  * @brief  OLED娓呭睆
  * @param  无
  * @retval 无
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
  * @brief  OLED鏄剧ず涓?涓?瓧绗?
  * @param  Line 琛屼綅缃?紝鑼冨洿锛?1~4
  * @param  Column 鍒椾綅缃?紝鑼冨洿锛?1~16
  * @param  Char 瑕佹樉绀虹殑涓?涓?瓧绗︼紝鑼冨洿锛欰SCII鍙??瀛楃?
  * @retval 无
  */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{      	
	uint8_t i;
	OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);		//璁剧疆鍏夋爣浣嶇疆鍦ㄤ笂鍗婇儴鍒?
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Char - ' '][i]);			//鏄剧ず涓婂崐閮ㄥ垎鍐呭?  绌哄瓧绗?scii涓?32
	}
	OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);	//璁剧疆鍏夋爣浣嶇疆鍦ㄤ笅鍗婇儴鍒?
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Char - ' '][i + 8]);		//鏄剧ず涓嬪崐閮ㄥ垎鍐呭?
	}
}

/**
  * @brief  OLED显示字符串
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  String 要显示的字符串，范围：ASCII可见字符
  * @retval 无
  */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)    //'\0'瀛楃?涓茬殑缁撳熬鏍囧織
	{
		OLED_ShowChar(Line, Column + i, String[i]);
	}
}

/**
  * @brief  OLED娆℃柟鍑芥暟
  * @retval 杩斿洖鍊肩瓑浜嶺鐨刌娆℃柟
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
  * @brief  OLED鏄剧ず鏁板瓧锛堝崄杩涘埗锛屾?鏁帮級
  * @param  Line 璧峰?琛屼綅缃?紝鑼冨洿锛?1~4
  * @param  Column 璧峰?鍒椾綅缃?紝鑼冨洿锛?1~16
  * @param  Number 瑕佹樉绀虹殑鏁板瓧锛岃寖鍥达細0~4294967295
  * @param  Length 瑕佹樉绀烘暟瀛楃殑闀垮害锛岃寖鍥达細1~10
  * @retval 无
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
  * @brief  OLED鏄剧ず鏁板瓧锛堝崄杩涘埗锛屽甫绗﹀彿鏁帮級
  * @param  Line 璧峰?琛屼綅缃?紝鑼冨洿锛?1~4
  * @param  Column 璧峰?鍒椾綅缃?紝鑼冨洿锛?1~16
  * @param  Number 瑕佹樉绀虹殑鏁板瓧锛岃寖鍥达細-2147483648~2147483647
  * @param  Length 瑕佹樉绀烘暟瀛楃殑闀垮害锛岃寖鍥达細1~10
  * @retval 无
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
  * @brief  OLED鏄剧ず鏁板瓧锛堝崄鍏?繘鍒讹紝姝ｆ暟锛?
  * @param  Line 璧峰?琛屼綅缃?紝鑼冨洿锛?1~4
  * @param  Column 璧峰?鍒椾綅缃?紝鑼冨洿锛?1~16
  * @param  Number 瑕佹樉绀虹殑鏁板瓧锛岃寖鍥达細0~0xFFFFFFFF
  * @param  Length 瑕佹樉绀烘暟瀛楃殑闀垮害锛岃寖鍥达細1~8
  * @retval 无
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
  * @brief  OLED鏄剧ず鏁板瓧锛堜簩杩涘埗锛屾?鏁帮級
  * @param  Line 璧峰?琛屼綅缃?紝鑼冨洿锛?1~4
  * @param  Column 璧峰?鍒椾綅缃?紝鑼冨洿锛?1~16
  * @param  Number 瑕佹樉绀虹殑鏁板瓧锛岃寖鍥达細0~1111 1111 1111 1111
  * @param  Length 瑕佹樉绀烘暟瀛楃殑闀垮害锛岃寖鍥达細1~16
  * @retval 无
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
  * @brief  OLED初始化
  * @param  无
  * @retval 无
  */
void OLED_Init(void)
{
	uint32_t i, j;
	
	for (i = 0; i < 1000; i++)			//涓婄數寤舵椂
	{
		for (j = 0; j < 1000; j++);
	}
	
	OLED_I2C_Init();			//绔?彛鍒濆?鍖?
	
	OLED_WriteCommand(0xAE);	//鍏抽棴鏄剧ず
	
	OLED_WriteCommand(0xD5);	//璁剧疆鏄剧ず鏃堕挓鍒嗛?姣?/鎸?崱鍣ㄩ?鐜?
	OLED_WriteCommand(0x80);
	
	OLED_WriteCommand(0xA8);	//璁剧疆澶氳矾澶嶇敤鐜?
	OLED_WriteCommand(0x3F);
	
	OLED_WriteCommand(0xD3);	//璁剧疆鏄剧ず鍋忕Щ
	OLED_WriteCommand(0x00);
	
	OLED_WriteCommand(0x40);	//璁剧疆鏄剧ず寮?濮嬭?
	
	OLED_WriteCommand(0xA1);	//璁剧疆宸﹀彸鏂瑰悜锛?0xA1姝ｅ父 0xA0宸﹀彸鍙嶇疆
	
	OLED_WriteCommand(0xC8);	//璁剧疆涓婁笅鏂瑰悜锛?0xC8姝ｅ父 0xC0涓婁笅鍙嶇疆

	OLED_WriteCommand(0xDA);	//璁剧疆COM寮曡剼纭?欢閰嶇疆
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);	//璁剧疆瀵规瘮搴︽帶鍒?
	OLED_WriteCommand(0xCF);

	OLED_WriteCommand(0xD9);	//璁剧疆棰勫厖鐢靛懆鏈?
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB);	//璁剧疆VCOMH鍙栨秷閫夋嫨绾у埆
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4);	//璁剧疆鏁翠釜鏄剧ず鎵撳紑/鍏抽棴

	OLED_WriteCommand(0xA6);	//璁剧疆姝ｅ父/鍊掕浆鏄剧ず

	OLED_WriteCommand(0x8D);	//璁剧疆鍏呯數娉?
	OLED_WriteCommand(0x14);

	OLED_WriteCommand(0xAF);	//寮?鍚?樉绀?
		
	OLED_Clear();				//OLED娓呭睆
}
/*
	显示汉字16*16
	行数1-4 列数1-8

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
	显示64*64的BMP图片
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
  * @brief  OLED涓囪兘鏄剧ず
  * @param  uint8_t Line	锛氳? 1-4
  * @param  uint8_t Column	锛氬垪 1-16
  * @param  float Float		锛氳?鏄剧ず鐨勬暟
  * @param  char *Char		锛氭樉绀虹殑娉ㄩ噴
  * @retval None
  */
void OLED_ShowFloat(uint8_t Line, uint8_t Column, float Float, char *Char)
{
	char txt[30];
	OLED_ShowString(Line, Column, Char);
	sprintf(txt,":%.1f ",Float);
	OLED_ShowString(Line, Column+strlen(Char),txt);
}