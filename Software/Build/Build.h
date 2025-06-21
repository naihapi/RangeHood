#ifndef _Build_H
#define _Build_H

// MCU型号
#include "stm32f10x.h"

// 软件
#include "Menu.h"
#include "UI.h"

// 外置硬件
#include "KEY.h"

// 变量
//...

// 宏定义
#define BUILD_SV_NOWPAGE_HOME 1   // 主页
#define BUILD_SV_NOWPAGE_MENU 2   // 菜单页
#define BUILD_SV_NOWPAGE_MODULE 3 // 组件页
#define BUILD_SV_NOWPAGE_CUSTOM 4 // 自定义页

// API
void Build_ControlPro(void);

#endif
