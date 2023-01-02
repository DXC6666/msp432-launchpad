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
}DOC_FRE_enum;//DCO可选频率

typedef enum{
	LFXTCLK,
	VLOCLK,
	REFOCLK,
	DCOCLK,
	MODOSC,
	HFXTCLK,
	DEFAULTSOURCE
}CLK_source_enum;//可选时钟源枚举

typedef enum{
	CLK_DIV1,//1分频
	CLK_DIV2,//2分频
	CLK_DIV4,//4分频
	CLK_DIV8,//8分频
	CLK_DIV16,//16分频
	CLK_DIV32,//32分频
	CLK_DIV64,//64分频
	CLK_DIV128,//128分频
}CLK_DIV_enum;//时钟信号可选分频列举

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