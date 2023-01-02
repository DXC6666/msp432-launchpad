/*-----------------------------------------------------------------------------------------------------
【平 台】Keil
【适 用 单 片 机】msp432P401R
【底 层 库】msp432_driverlib_3_21_00_05
【开 发】lv
* @@ 库仅供参考 后果自负
* 头文件
* 其他头文件最好不要包含.h文件 很容易一不小心就变成嵌套包含导致声明文件无效
* .h文件不要定义变量  定义了变量只在用的.c文件里声明  .h只进行类型的定义和声明
* 版本 v1.0
* 时间 2022年12月27日16:39:03
-------------------------------------------------------------------------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

#include "driverlib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "delay.h"
#include "sys.h"
#include "EXTI.h"
#include "led.h"
#include "soft_interrupt.h"
#include "myuart.h"
#include "key.h"
#include "TimerA.h"
#include "MyGPIO.h"
#include "servo.h"
#include "MyGPIO.h"

#include "OLED.h"


#include "OLED_SPI.h"

#include "VOFA.h"

#endif

