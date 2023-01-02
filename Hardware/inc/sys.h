#ifndef __SYS_H__
#define __SYS_H__


typedef enum{
	DCO_1_5M,
	DCO_3_0M,
	DCO_6_0M,
	DCO_12_0M,
	DCO_24_0M,
	DCO_48_0M,
	DC0_DEFAULTFRE
}DOC_FRE_enum;//DCO��ѡƵ��

typedef enum{
	LFXTCLK,
	VLOCLK,
	REFOCLK,
	DCOCLK,
	MODOSC,
	HFXTCLK,
	DEFAULTSOURCE
}CLK_source_enum;//��ѡʱ��Դö��

typedef enum{
	CLK_DIV1,//1��Ƶ
	CLK_DIV2,//2��Ƶ
	CLK_DIV4,//4��Ƶ
	CLK_DIV8,//8��Ƶ
	CLK_DIV16,//16��Ƶ
	CLK_DIV32,//32��Ƶ
	CLK_DIV64,//64��Ƶ
	CLK_DIV128,//128��Ƶ
}CLK_DIV_enum;//ʱ���źſ�ѡ��Ƶ�о�

typedef	struct
{
	uint32_t	ACLK;
	uint32_t	MCLK;
	uint32_t	HSMCLK;
	uint32_t	SMCLK;
	uint32_t	BCLK;
}SysClkStruct;






void Clock_get(SysClkStruct *SysClock_Handle);
void SysInit(void);
#endif