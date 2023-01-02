/*-----------------------------------------------------------------------------------------------------
¡¾Æ½ Ì¨¡¿Keil
¡¾ÊÊ ÓÃ µ¥ Æ¬ »ú¡¿msp432P401R
¡¾µ× ²ã ¿â¡¿msp432_driverlib_3_21_00_05
¡¾¿ª ·¢¡¿lv
* @@ ¿â½ö¹©²Î¿¼ ºó¹û×Ô¸º
* OLED  Ä£ÄâIIC×ÊÔ´½éÉÜ
* SCL      :   P3.6
* SDA      :   P3.7
* °æ±¾ v1.0
* Ê±¼ä 2022Äê12ÔÂ27ÈÕ16:39:03
-------------------------------------------------------------------------------------------------------*/
#include "main.h"
#include "OLED_Font.h"  


/*Òı½ÅÅäÖÃ*/
#define OLED_W_SCL(x)		GPIO_WriteBit(GPIO_PORT_P3, GPIO_PIN6, (x))
#define OLED_W_SDA(x)		GPIO_WriteBit(GPIO_PORT_P3, GPIO_PIN7, (x))

/*Òı½Å³õÊ¼»¯*/
void OLED_I2C_Init(void)
{
   

	GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN6);
	GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN7);
	
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}

/**
  * @brief  I2C¿ªÊ¼
  * @param  ÎŞ
  * @retval ÎŞ
  */
void OLED_I2C_Start(void)
{
	OLED_W_SDA(1);
	OLED_W_SCL(1);
	OLED_W_SDA(0);
	OLED_W_SCL(0);
}

/**
  * @brief  I2CÍ£Ö¹
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
  * @brief  I2C·¢ËÍÒ»¸ö×Ö½Ú
  * @param  Byte Òª·¢ËÍµÄÒ»¸ö×Ö½Ú
  * @retval ÎŞ
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
	OLED_W_SCL(1);	//é¢å?çš„ä¸€ä¸?—¶é’Ÿï¼Œä¸å?ç†åº”ç­”ä¿¡å?
	OLED_W_SCL(0);
}

/**
  * @brief  OLEDĞ´ÃüÁî
  * @param  Command ÒªĞ´ÈëµÄÃüÁî
  * @retval ÎŞ
  */
void OLED_WriteCommand(uint8_t Command)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//´Ó»úµØÖ·
	OLED_I2C_SendByte(0x00);		//Ğ´ÃüÁî Co=0 D/C=0 000 000
	OLED_I2C_SendByte(Command); 
	OLED_I2C_Stop();
}

/**
  * @brief  OLEDĞ´Êı¾İ
  * @param  Data ÒªĞ´ÈëµÄÊı¾İ
  * @retval ÎŞ
  */
void OLED_WriteData(uint8_t Data)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//´Ó»úµØÖ·
	OLED_I2C_SendByte(0x40);		//Ğ´Êı¾İ Co=0 D/C=1 000 000
	OLED_I2C_SendByte(Data);
	OLED_I2C_Stop();
}

/**
  * @brief  OLEDè®¾ç½®å…‰æ ‡ä½ç½®
  * @param  Y ä»¥å·¦ä¸Šè?ä¸ºåŸç‚¹ï¼Œå‘ä¸‹æ–¹å‘çš„åæ ‡ï¼ŒèŒƒå›´ï¼?0~7
  * @param  X ä»¥å·¦ä¸Šè?ä¸ºåŸç‚¹ï¼Œå‘å³æ–¹å‘çš„åæ ‡ï¼ŒèŒƒå›´ï¼?0~127
  * @retval ÎŞ
  */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
	OLED_WriteCommand(0xB0 | Y);					//è®¾ç½®é¡µä½ç½?           åˆ—åœ°å€é«˜å››ä½çš„å‰?4ä½å›ºå®šæ˜¯0b0001,ä½å››ä½çš„å‰?4ä½å›ºå®šæ˜¯0b0000
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//è®¾ç½®åˆ—ä½ç½?«˜4ä½?
	OLED_WriteCommand((X & 0x0F));					//è®¾ç½®åˆ—ä½ç½?½4ä½?
}

/**
  * @brief  OLEDæ¸…å±
  * @param  ÎŞ
  * @retval ÎŞ
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
  * @brief  OLEDæ˜¾ç¤ºä¸€ä¸?­—ç¬?
  * @param  Line è¡Œä½ç½?¼ŒèŒƒå›´ï¼?1~4
  * @param  Column åˆ—ä½ç½?¼ŒèŒƒå›´ï¼?1~16
  * @param  Char è¦æ˜¾ç¤ºçš„ä¸€ä¸?­—ç¬¦ï¼ŒèŒƒå›´ï¼šASCIIå??å­—ç?
  * @retval ÎŞ
  */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{      	
	uint8_t i;
	OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);		//è®¾ç½®å…‰æ ‡ä½ç½®åœ¨ä¸ŠåŠéƒ¨åˆ?
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Char - ' '][i]);			//æ˜¾ç¤ºä¸ŠåŠéƒ¨åˆ†å†…å?  ç©ºå­—ç¬?sciiä¸?32
	}
	OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);	//è®¾ç½®å…‰æ ‡ä½ç½®åœ¨ä¸‹åŠéƒ¨åˆ?
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Char - ' '][i + 8]);		//æ˜¾ç¤ºä¸‹åŠéƒ¨åˆ†å†…å?
	}
}

/**
  * @brief  OLEDÏÔÊ¾×Ö·û´®
  * @param  Line ÆğÊ¼ĞĞÎ»ÖÃ£¬·¶Î§£º1~4
  * @param  Column ÆğÊ¼ÁĞÎ»ÖÃ£¬·¶Î§£º1~16
  * @param  String ÒªÏÔÊ¾µÄ×Ö·û´®£¬·¶Î§£ºASCII¿É¼û×Ö·û
  * @retval ÎŞ
  */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)    //'\0'å­—ç?ä¸²çš„ç»“å°¾æ ‡å¿—
	{
		OLED_ShowChar(Line, Column + i, String[i]);
	}
}

/**
  * @brief  OLEDæ¬¡æ–¹å‡½æ•°
  * @retval è¿”å›å€¼ç­‰äºXçš„Yæ¬¡æ–¹
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
  * @brief  OLEDæ˜¾ç¤ºæ•°å­—ï¼ˆåè¿›åˆ¶ï¼Œæ?æ•°ï¼‰
  * @param  Line èµ·å?è¡Œä½ç½?¼ŒèŒƒå›´ï¼?1~4
  * @param  Column èµ·å?åˆ—ä½ç½?¼ŒèŒƒå›´ï¼?1~16
  * @param  Number è¦æ˜¾ç¤ºçš„æ•°å­—ï¼ŒèŒƒå›´ï¼š0~4294967295
  * @param  Length è¦æ˜¾ç¤ºæ•°å­—çš„é•¿åº¦ï¼ŒèŒƒå›´ï¼š1~10
  * @retval ÎŞ
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
  * @brief  OLEDæ˜¾ç¤ºæ•°å­—ï¼ˆåè¿›åˆ¶ï¼Œå¸¦ç¬¦å·æ•°ï¼‰
  * @param  Line èµ·å?è¡Œä½ç½?¼ŒèŒƒå›´ï¼?1~4
  * @param  Column èµ·å?åˆ—ä½ç½?¼ŒèŒƒå›´ï¼?1~16
  * @param  Number è¦æ˜¾ç¤ºçš„æ•°å­—ï¼ŒèŒƒå›´ï¼š-2147483648~2147483647
  * @param  Length è¦æ˜¾ç¤ºæ•°å­—çš„é•¿åº¦ï¼ŒèŒƒå›´ï¼š1~10
  * @retval ÎŞ
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
  * @brief  OLEDæ˜¾ç¤ºæ•°å­—ï¼ˆåå…?¿›åˆ¶ï¼Œæ­£æ•°ï¼?
  * @param  Line èµ·å?è¡Œä½ç½?¼ŒèŒƒå›´ï¼?1~4
  * @param  Column èµ·å?åˆ—ä½ç½?¼ŒèŒƒå›´ï¼?1~16
  * @param  Number è¦æ˜¾ç¤ºçš„æ•°å­—ï¼ŒèŒƒå›´ï¼š0~0xFFFFFFFF
  * @param  Length è¦æ˜¾ç¤ºæ•°å­—çš„é•¿åº¦ï¼ŒèŒƒå›´ï¼š1~8
  * @retval ÎŞ
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
  * @brief  OLEDæ˜¾ç¤ºæ•°å­—ï¼ˆäºŒè¿›åˆ¶ï¼Œæ?æ•°ï¼‰
  * @param  Line èµ·å?è¡Œä½ç½?¼ŒèŒƒå›´ï¼?1~4
  * @param  Column èµ·å?åˆ—ä½ç½?¼ŒèŒƒå›´ï¼?1~16
  * @param  Number è¦æ˜¾ç¤ºçš„æ•°å­—ï¼ŒèŒƒå›´ï¼š0~1111 1111 1111 1111
  * @param  Length è¦æ˜¾ç¤ºæ•°å­—çš„é•¿åº¦ï¼ŒèŒƒå›´ï¼š1~16
  * @retval ÎŞ
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
  * @brief  OLED³õÊ¼»¯
  * @param  ÎŞ
  * @retval ÎŞ
  */
void OLED_Init(void)
{
	uint32_t i, j;
	
	for (i = 0; i < 1000; i++)			//ä¸Šç”µå»¶æ—¶
	{
		for (j = 0; j < 1000; j++);
	}
	
	OLED_I2C_Init();			//ç«?£åˆå?åŒ?
	
	OLED_WriteCommand(0xAE);	//å…³é—­æ˜¾ç¤º
	
	OLED_WriteCommand(0xD5);	//è®¾ç½®æ˜¾ç¤ºæ—¶é’Ÿåˆ†é?æ¯?/æŒ?¡å™¨é?ç?
	OLED_WriteCommand(0x80);
	
	OLED_WriteCommand(0xA8);	//è®¾ç½®å¤šè·¯å¤ç”¨ç?
	OLED_WriteCommand(0x3F);
	
	OLED_WriteCommand(0xD3);	//è®¾ç½®æ˜¾ç¤ºåç§»
	OLED_WriteCommand(0x00);
	
	OLED_WriteCommand(0x40);	//è®¾ç½®æ˜¾ç¤ºå¼€å§‹è?
	
	OLED_WriteCommand(0xA1);	//è®¾ç½®å·¦å³æ–¹å‘ï¼?0xA1æ­£å¸¸ 0xA0å·¦å³åç½®
	
	OLED_WriteCommand(0xC8);	//è®¾ç½®ä¸Šä¸‹æ–¹å‘ï¼?0xC8æ­£å¸¸ 0xC0ä¸Šä¸‹åç½®

	OLED_WriteCommand(0xDA);	//è®¾ç½®COMå¼•è„šç¡?»¶é…ç½®
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);	//è®¾ç½®å¯¹æ¯”åº¦æ§åˆ?
	OLED_WriteCommand(0xCF);

	OLED_WriteCommand(0xD9);	//è®¾ç½®é¢„å……ç”µå‘¨æœ?
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB);	//è®¾ç½®VCOMHå–æ¶ˆé€‰æ‹©çº§åˆ«
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4);	//è®¾ç½®æ•´ä¸ªæ˜¾ç¤ºæ‰“å¼€/å…³é—­

	OLED_WriteCommand(0xA6);	//è®¾ç½®æ­£å¸¸/å€’è½¬æ˜¾ç¤º

	OLED_WriteCommand(0x8D);	//è®¾ç½®å……ç”µæ³?
	OLED_WriteCommand(0x14);

	OLED_WriteCommand(0xAF);	//å¼€å?˜¾ç¤?
		
	OLED_Clear();				//OLEDæ¸…å±
}
/*
	ÏÔÊ¾ºº×Ö16*16
	ĞĞÊı1-4 ÁĞÊı1-8

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
	ÏÔÊ¾64*64µÄBMPÍ¼Æ¬
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
  * @brief  OLEDä¸‡èƒ½æ˜¾ç¤º
  * @param  uint8_t Line	ï¼šè? 1-4
  * @param  uint8_t Column	ï¼šåˆ— 1-16
  * @param  float Float		ï¼šè?æ˜¾ç¤ºçš„æ•°
  * @param  char *Char		ï¼šæ˜¾ç¤ºçš„æ³¨é‡Š
  * @retval None
  */
void OLED_ShowFloat(uint8_t Line, uint8_t Column, float Float, char *Char)
{
	char txt[30];
	OLED_ShowString(Line, Column, Char);
	sprintf(txt,":%.1f ",Float);
	OLED_ShowString(Line, Column+strlen(Char),txt);
}