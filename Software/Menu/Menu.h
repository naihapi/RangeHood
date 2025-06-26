#ifndef _Menu_H
#define _Menu_H

// 标准库
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// MCU型号
#include "stm32f10x.h"

// 外设
//...

// 外置硬件
#include "OLED.h"

// 软件
//...

// 宏定义
#define ItemType_Switch 1         // 菜单项类型-开关型
#define ItemType_Slider 2         // 菜单项类型-滑块型
#define ItemType_View 3           // 菜单项类型-视图型
#define ItemType_Custom 4         // 菜单项类型-自定义型
#define SliderModule_YesSetting 1 // 滑块型组件-允许跳转最大、最小值的设置
#define SliderModule_NotSetting 0 // 滑块型组件-不允许跳转最大、最小值的设置

// 菜单（1个菜单项所包含的信息）
typedef struct MenuItem
{
    const uint8_t *Icon;   // 图标路径
    uint8_t *Title;        // 菜单项标题
    uint8_t ItemType;      // 菜单项类型(ItemType_xxx)
    void *Function;        // 指向一个函数
    void *ItemPointer;     // 具体组件数据(Menu_xxxModule)
    uint8_t *Name;         // 外置硬件的名称
    struct MenuItem *Last; // 指向上一个菜单项
    struct MenuItem *Next; // 指向下一个菜单项
} MenuItem;

// 主页（1个主页项所包含的信息）
typedef struct MenuHome
{
    const uint8_t *Icon;   // 图标路径
    uint8_t *Title;        // 主页标题
    struct MenuItem *Menu; // 主页选定的菜单
    int8_t *MaxItem;       // 主页选定的菜单项最大个数
    struct MenuHome *Last; // 指向上一个主页项的指针
    struct MenuHome *Next; // 指向下一个主页项的指针
} MenuHome;

// 开关型组件（1个开关型组件项所包含的信息）
typedef struct Menu_SwitchModule
{
    uint8_t *State; // 指向开关状态的指针
} Menu_SwitchModule;

// 视图型组件（1个视图型组件所包含的信息）
typedef struct Menu_ViewModule
{
    uint8_t *Description; // 描述信息
    int *Value;           // 数值
} Menu_ViewModule;

// 滑块型组件（1个滑块型组件所包含的信息）
typedef struct Menu_SliderModule
{
    int *NowValue;   // 指向当前值
    int *MaxValue;   // 指向最大值
    int *MiniValue;  // 指向最小值
    uint8_t Setting; // 是否可以调整最大、最小值(SliderModule_xxxSetting)
    uint8_t *Unit;   // 单位
} Menu_SliderModule;

// // 变量
// extern int8_t Menu_MaxItem_Home;
// extern int8_t Menu_MaxItem_Light;
// extern int8_t Menu_MaxItem_Sensor;
// extern int8_t Menu_MaxItem_Cruise;
// extern MenuHome *Menu_Head_Home;
// extern MenuItem *Menu_Head_Light;
// extern MenuItem *Menu_Head_Sensor;
// extern MenuItem *Menu_Head_Cruise;
// extern MenuItem *Menu_Head_Circle;
// extern uint8_t Menu_Title_System[];
// extern uint8_t State_OLEDDirection_LR;
// extern uint8_t State_OLEDDirection_TB;
// extern uint8_t State_Reset;
// extern int Value_OLED_NowBrightness;
// extern int Value_OLED_MaxBrightness;
// extern int Value_OLED_MiniBrightness;
// extern int Value_FreeHeap;

// API
MenuHome *Menu_CreateHomeItem(const uint8_t *icon, uint8_t *title, MenuItem *menu, int8_t *maxitem);
MenuItem *Menu_CreateItem(const uint8_t *icon, uint8_t type, void *function, void *pointer, uint8_t *name);
Menu_SwitchModule *Mneu_CreateSwitchModule(uint8_t *state);
Menu_ViewModule *Menu_CreateViewModule(uint8_t *description, int *value);
Menu_SliderModule *Menu_CreateSliderModule(int *nowvalue, int *maxvalue, int *minivalue, uint8_t setting, uint8_t *unit);
MenuItem *Menu_CreateSwitchItem(const uint8_t *icon, uint8_t *name, uint8_t *state);
MenuItem *Menu_CreateViewItem(const uint8_t *icon, uint8_t *name, uint8_t *description, int *value);
MenuItem *Menu_CreateSliderItem(const uint8_t *icon, uint8_t *name, int *nowvalue, int *maxvalue, int *minivalue, uint8_t *unit, uint8_t setting);
MenuItem *Menu_CreateCustomItem(const uint8_t *icon, uint8_t *name, void *function);
MenuHome *Menu_RetHomeItem(MenuHome *Head, uint8_t item);
MenuItem *Menu_RetMenuItem(MenuItem *Head, uint8_t item);
int8_t Menu_GetHomeMaxItem(MenuHome *head);
int8_t Menu_GetMenuMaxItem(MenuItem *head);
MenuHome *Menu_GetHomeEndItem(MenuHome *head);
MenuItem *Menu_GetMenuEndItem(MenuItem *head);
void Menu_ItemEachOther(MenuItem **nowitem, MenuItem *lastitem, MenuItem *nextitem);
void Menu_Include_HomeItem(MenuHome *head, MenuHome *item);
void Menu_Include_MenuItem(MenuItem *head, MenuItem *item);
MenuHome *Menu_CreateHomeHead(void);
MenuItem *Menu_CreateMenuHead(uint8_t *title);

#endif
