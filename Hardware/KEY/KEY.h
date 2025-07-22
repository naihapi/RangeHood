#ifndef _KEY_H
#define _KEY_H

// MCU型号
#include "stm32f10x.h"

// 硬件
#include "GPIO.h"

// RTOS头文件
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "MyTASK.h"

// 变量
extern uint8_t KEY_Count;

// 宏定义
#define KEY1_TASK TASK1_Handler // 按键1任务
#define KEY2_TASK TASK2_Handler // 按键2任务
#define KEY3_TASK TASK3_Handler // 按键3任务
#define KEY_STATE_UPNONE 0      // 按键松开
#define KEY_STATE_DOWNSHORT 1   // 按键短按
#define KEY_STATE_DOWNLONG 2    // 按键长按
#define KEY_NUMBER_1 1          // 按键编号1
#define KEY_NUMBER_2 2          // 按键编号2
#define KEY_NUMBER_3 3          // 按键编号3

// API
void KEY_InitPro(void);
void KEY1_Scanf(void);
void KEY2_Scanf(void);
void KEY3_Scanf(void);
void KEY_KEYScanf_Disable(void);
void KEY_KEYScanf_Enable(void);
void KEY_SetState(uint8_t Keyx, uint8_t State);
void KEY_ClearState(uint8_t Keyx);
uint8_t KEY_RetState(uint8_t Keyx);

#endif
