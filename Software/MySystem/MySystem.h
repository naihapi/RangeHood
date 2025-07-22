#ifndef __MySystem_H__
#define __MySystem_H__

// 标准库
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// MCU型号
#include "stm32f10x.h"

// 硬件
#include "WS2812.h"

// 软件
#include "MyMenu.h"

// 外设
#include "TIM.h"

// 宏定义
#define MYSYSTEM_WS2812_NUMBER 12     // WS2812灯珠数量
#define MYSYSTEM_WS2812_GC_REDUCE 0   // WS2812灯珠渐变方向-减少
#define MYSYSTEM_WS2812_GC_INCREASE 1 // WS2812灯珠渐变方向-增加

// API
void MySystem_OLED_Function(void);
void MySystem_Fanlight_GradualChange_Same_Init(void);
void MySystem_Fanlight_GradualChange_Same(void);
void MySystem_Fanlight_Update(void);
void MySystem_GetFreeHeap(void);
void MySystem_FanSpeed_Function(void);
void MySystem_Fanlight_Function_Init(void);
void MySystem_Fanlight_Function(void);
void MySystem_Lock_Function(void);

#endif
