#ifndef _MAIN_H
#define _MAIN_H

// 标准库
#include "stdio.h"
#include "stdbool.h"

// MCU型号
#include "stm32f10x.h"

// RTOS
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

// 外置硬件
#include "OLED.h"

// 软件
#include "MyTask.h"
#include "Delay.h"
#include "Build.h"
#include "Menu.h"

// 外设
#include "TIM.h"
#include "GPIO.h"

#endif
