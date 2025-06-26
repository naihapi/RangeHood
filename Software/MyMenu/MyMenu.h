#ifndef __MYMENU_H__
#define __MYMENU_H__

// MCU型号
#include "stm32f10x.h"

// 软件
#include "Menu.h"
#include "Build.h"

// 变量
extern int8_t Menu_MaxItem_Home;
extern int8_t Menu_MaxItem_Light;
extern int8_t Menu_MaxItem_Sensor;
extern int8_t Menu_MaxItem_Cruise;
extern MenuHome *Menu_Head_Home;
extern MenuItem *Menu_Head_Light;
extern MenuItem *Menu_Head_Sensor;
extern MenuItem *Menu_Head_Cruise;
extern MenuItem *Menu_Head_Circle;
extern uint8_t Menu_Title_System[];
extern uint8_t State_OLEDDirection_LR;
extern uint8_t State_OLEDDirection_TB;
extern uint8_t State_Reset;
extern int Value_OLED_NowBrightness;
extern int Value_OLED_MaxBrightness;
extern int Value_OLED_MiniBrightness;
extern int Value_FreeHeap;

// API
void MyMenu_InitPro(void);

#endif
