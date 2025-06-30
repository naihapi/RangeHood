#ifndef __MYMENU_H__
#define __MYMENU_H__

// MCU型号
#include "stm32f10x.h"

// 软件
#include "Menu.h"
#include "Build.h"

// 变量
typedef struct MenuItem MenuItem;
typedef struct MenuHome MenuHome;
extern uint8_t State_OLEDDirection_LR;
extern uint8_t State_OLEDDirection_TB;
extern uint8_t State_OLEDMode;
extern int Value_OLED_NowBrightness;
extern MenuHome *Menu_Head_Home;
extern int8_t Menu_MaxItem_Home;
extern int Value_FreeHeap;
extern int Value_Fan_NowSpeed;
extern uint8_t State_Fan;

// API
void MyMenu_InitPro(void);

#endif
