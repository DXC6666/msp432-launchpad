/*-----------------------------------------------------------------------------------------------------
【平 台】Keil
【适 用 单 片 机】msp432P401R
【底 层 库】msp432_driverlib_3_21_00_05
【开 发】lv
* @@ 库仅供参考 后果自负
* OLED 四线SPI 资源介绍
*               GND    电源地
*								VCC  接5V或3.3v电源
*								D0   接P6.0（SCL）
*								D1   接P4.3（SDA）
*								RES  接P4.0
*								DC   接P6.1
*								CS   接P1.5     
* 
* 版本 v1.0
* 时间 2022年12月27日16:39:03
-------------------------------------------------------------------------------------------------------*/
#ifndef __OLED_SPI_H__
#define __OLED_SPI_H__			  	 
// #include "sys.h"
// #include "stdlib.h"	   

//OLED模式设置
//0:4线串行模式
//1:并行8080模式
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    

//-----------------测试LED端口定义---------------- 
// #define LED_ON GPIO_ResetBits(GPIOB,GPIO_Pin_8)//DC
// #define LED_OFF GPIO_SetBits(GPIOB,GPIO_Pin_8)

#define LED_ON  GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN1)   //DC
#define LED_OFF GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN1)

//-----------------OLED端口定义----------------  					   


// #define OLED_SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_5)//CLK
// #define OLED_SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_5)

// #define OLED_SDIN_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_7)//DIN
// #define OLED_SDIN_Set() GPIO_SetBits(GPIOA,GPIO_Pin_7)

// #define OLED_RST_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_0)//RES
// #define OLED_RST_Set() GPIO_SetBits(GPIOB,GPIO_Pin_0)

// #define OLED_DC_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_1)//DC
// #define OLED_DC_Set() GPIO_SetBits(GPIOB,GPIO_Pin_1)
 		     
// #define OLED_CS_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_4)//CS
// #define OLED_CS_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_4)

#define OLED_SCLK_Clr() GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0) //CLK  
#define OLED_SCLK_Set() GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN0)

#define OLED_SDIN_Clr() GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3) //DIN
#define OLED_SDIN_Set() GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3)

#define OLED_RST_Clr()  GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0) //RES
#define OLED_RST_Set()  GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0)

#define OLED_DC_Clr()   GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN1) //DC
#define OLED_DC_Set()   GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN1)
 		     
#define OLED_CS_Clr()   GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5) //CS
#define OLED_CS_Set()   GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN5)


#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//OLED控制用函数
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_SPI_Clear(void);
void OLED_SPI_Init(void);

//void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
//void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);

void OLED_SPI_ShowChar(uint8_t x, uint8_t y, uint8_t chr);

void OLED_SPI_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size);
void OLED_SPI_ShowString(uint8_t x, uint8_t y, uint8_t *chr);

void OLED_SPI_ShowCHinese(uint8_t x, uint8_t y, uint8_t no);
void OLED_SPI_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[]);
void OLED_Set_Pos(unsigned char x, unsigned char y);


#endif  
	 



