#include "MyMenu.h"

/*---菜单项名称---*/
uint8_t Name_Fan_State[] = "State";           // 风扇状态
uint8_t Name_Fan_Speed[] = "Speed";           // 风扇速度
uint8_t Name_Light_State[] = "State";         // 灯光状态
uint8_t Name_Light_Auto[] = "Auto";           // 灯光自动模式
uint8_t Name_Light_Red[] = "Red";             // 红色灯光
uint8_t Name_Light_Green[] = "Green";         // 绿色灯光
uint8_t Name_Light_Blue[] = "Blue";           // 蓝色灯光
uint8_t Name_Lock_State[] = "State";          // 锁屏状态
uint8_t Name_Lock_Change[] = "Change";        // 锁屏切换
uint8_t Name_OLEDMode[] = "Display";          // 系统-OLED显示模式
uint8_t Name_OLEDBrightness[] = "Brightness"; // 系统-OLED亮度
uint8_t Name_OLEDDirection_LR[] = "Dir-LR";   // 系统-OLED左右方向
uint8_t Name_OLEDDirection_TB[] = "Dir-TB";   // 系统-OLED上下方向
uint8_t Name_FreeHeap[] = "OSFreeHeap";       // 系统-剩余堆空间
/*---菜单项名称---*/

/*---状态(开关组件)---*/
uint8_t State_Fan = 1;              // 风扇开关状态（0：关闭，1：开启）
uint8_t State_Light = 1;            // 灯开关状态（0：关闭，1：开启）
uint8_t State_Light_Auto = 1;       // 灯自动模式（0：手动模式，1：自动模式）
uint8_t State_Lock = 1;             // 锁屏状态（0：关闭，1：打开）
uint8_t State_OLEDMode = 0;         // 系统-OLED显示模式（0：深色系，1：浅色系）
uint8_t State_OLEDDirection_LR = 1; // 系统-OLED显示左右方向（0：正常，1：左右反置）
uint8_t State_OLEDDirection_TB = 1; // 系统-OLED显示上下方向（0：正常，1：上下反置）
/*---状态(开关组件)---*/

/*---数值(视图组件/滑块组件)---*/
int Value_Lock_NowStyle = 1;         // 息屏当前样式
int Value_Lock_MiniStyle = 0;        // 锁屏最小个数
int Value_Lock_MaxStyle = 4;         // 锁屏最大个数
int Value_Fan_NowSpeed = 5;          // 风扇当前速度
int Value_Fan_MaxSpeed = 5;          // 风扇最大速度
int Value_Fan_MiniSpeed = 1;         // 风扇最小速度
int Value_Light_Red_NowColor = 1;    // 当前红色数值
int Value_Light_Red_MaxColor = 20;   // 最大红色数值
int Value_Light_Red_MiniColor = 0;   // 最小红色数值
int Value_Light_Green_NowColor = 1;  // 当前绿色数值
int Value_Light_Green_MaxColor = 20; // 最大绿色数值
int Value_Light_Green_MiniColor = 0; // 最小绿色数值
int Value_Light_Blue_NowColor = 1;   // 当前蓝色数值
int Value_Light_Blue_MaxColor = 20;  // 最大蓝色数值
int Value_Light_Blue_MiniColor = 0;  // 最小蓝色数值
int Value_OLED_NowBrightness = 2;    // 系统-OLED当前亮度
int Value_OLED_MaxBrightness = 3;    // 系统-OLED可调节的最大亮度
int Value_OLED_MiniBrightness = 1;   // 系统-OLED可调节的最小亮度
int Value_FreeHeap = 0;              // 系统-剩余堆空间
/*---数值(视图组件/滑块组件)---*/

/*---单位(滑块组件)---*/
uint8_t Unit_Lock_Style[] = "Single";          // 锁定样式-个
uint8_t Unit_Fan_Speed[] = "Gears";            // 风扇风速-档位
uint8_t Unit_Light_RGBxColor[] = "Proportion"; // RGB颜色-占比
uint8_t Unit_OLED_BrightnessGear[] = "Gears";  // 系统-OLED亮度-档位
/*---单位(滑块组件)---*/

/*---描述(视图组件)---*/
uint8_t Description_FreeHeap[] = "Byte"; // 系统-剩余堆字节
/*---描述(视图组件)---*/

/*---主页项标题---*/
uint8_t Menu_Title_Lock[] = {"Lock"};     // 锁屏
uint8_t Menu_Title_System[] = {"System"}; // 系统
uint8_t Menu_Title_Fan[] = {"Fan"};       // 风扇
uint8_t Menu_Title_Light[] = {"Light"};   // 灯光
/*---主页项标题---*/

/*---最大项---*/
int8_t Menu_MaxItem_Home = 0;   // 主页项
int8_t Menu_MaxItem_System = 0; // 系统菜单项
int8_t Menu_MaxItem_Fan = 0;    // 风扇菜单项
int8_t Menu_MaxItem_Light = 0;  // 灯光菜单项
int8_t Menu_MaxItem_Lock = 0;   // 锁屏菜单项
/*---最大项---*/

/*---主页项---*/
MenuHome *Menu_Head_Home;   // 主页头
MenuItem *Menu_Head_System; // 系统页
MenuItem *Menu_Head_Fan;    // 风扇页
MenuItem *Menu_Head_Light;  // 灯光页
MenuItem *Menu_Head_Lock;   // 锁屏页
/*---主页项---*/

/**
 * @brief 创建主页项
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void MyMenu_Create_HomeItem(void)
{
    // 创建主页头
    Menu_Head_Home = Menu_CreateHomeHead();

    // 创建项
    MenuHome *system = Menu_CreateHomeItem(OLEDData_Icon_HomeItem_System, Menu_Title_System, Menu_Head_System, &Menu_MaxItem_System);
    MenuHome *fan = Menu_CreateHomeItem(OLEDData_Icon_HomeItem_Fan, Menu_Title_Fan, Menu_Head_Fan, &Menu_MaxItem_Fan);
    MenuHome *light = Menu_CreateHomeItem(OLEDData_Icon_HomeItem_Light, Menu_Title_Light, Menu_Head_Light, &Menu_MaxItem_Light);
    MenuHome *lock = Menu_CreateHomeItem(OLEDData_Icon_HomeItem_Lock, Menu_Title_Lock, Menu_Head_Lock, &Menu_MaxItem_Lock);

    // 菜单头包含
    Menu_Include_HomeItem(Menu_Head_Home, system);
    Menu_Include_HomeItem(Menu_Head_Home, fan);
    Menu_Include_HomeItem(Menu_Head_Home, light);
    Menu_Include_HomeItem(Menu_Head_Home, lock);
}

/**
 * @brief 创建“系统设置”菜单项
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void MyMenu_Create_MenuItem_System(void)
{
    // 创建菜单头
    Menu_Head_System = Menu_CreateMenuHead(Menu_Title_System);

    // 创建项
    MenuItem *mode = Menu_CreateSwitchItem(OLEDData_Icon_Display, Name_OLEDMode, &State_OLEDMode);
    MenuItem *brightness = Menu_CreateSliderItem(OLEDData_Icon_Brightness, Name_OLEDBrightness, &Value_OLED_NowBrightness, &Value_OLED_MaxBrightness, &Value_OLED_MiniBrightness, Unit_OLED_BrightnessGear, SliderModule_NotSetting);
    MenuItem *dirlr = Menu_CreateSwitchItem(OLEDData_Icon_DirLR, Name_OLEDDirection_LR, &State_OLEDDirection_LR);
    MenuItem *dirtb = Menu_CreateSwitchItem(OLEDData_Icon_DirTB, Name_OLEDDirection_TB, &State_OLEDDirection_TB);
    MenuItem *heap = Menu_CreateViewItem(OLEDData_Icon_FreeHeap, Name_FreeHeap, Description_FreeHeap, &Value_FreeHeap);

    // 菜单头包含
    Menu_Include_MenuItem(Menu_Head_System, mode);
    Menu_Include_MenuItem(Menu_Head_System, brightness);
    Menu_Include_MenuItem(Menu_Head_System, dirlr);
    Menu_Include_MenuItem(Menu_Head_System, dirtb);
    Menu_Include_MenuItem(Menu_Head_System, heap);
}

/**
 * @brief 创建“风扇”菜单项
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void MyMenu_Create_MenuItem_Fan(void)
{
    // 创建菜单头
    Menu_Head_Fan = Menu_CreateMenuHead(Menu_Title_Fan);

    // 创建项
    MenuItem *fanstate = Menu_CreateSwitchItem(OLEDData_Icon_FanState, Name_Fan_State, &State_Fan);
    MenuItem *fanspeed = Menu_CreateSliderItem(OLEDData_Icon_FanSpeed, Name_Fan_Speed, &Value_Fan_NowSpeed, &Value_Fan_MaxSpeed, &Value_Fan_MiniSpeed, Unit_Fan_Speed, SliderModule_NotSetting);

    // 菜单头包含
    Menu_Include_MenuItem(Menu_Head_Fan, fanstate);
    Menu_Include_MenuItem(Menu_Head_Fan, fanspeed);
}

/**
 * @brief 创建“灯光”菜单项
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void MyMenu_Create_MenuItem_Light(void)
{
    // 创建菜单头
    Menu_Head_Light = Menu_CreateMenuHead(Menu_Title_Light);

    // 创建项
    MenuItem *state = Menu_CreateSwitchItem(OLEDData_Icon_LightState, Name_Light_State, &State_Light);
    MenuItem *myauto = Menu_CreateSwitchItem(OLEDData_Icon_LightAuto, Name_Light_Auto, &State_Light_Auto);
    MenuItem *r = Menu_CreateSliderItem(OLEDData_Icon_Red, Name_Light_Red, &Value_Light_Red_NowColor, &Value_Light_Red_MaxColor, &Value_Light_Red_MiniColor, Unit_Light_RGBxColor, SliderModule_NotSetting);
    MenuItem *g = Menu_CreateSliderItem(OLEDData_Icon_Green, Name_Light_Green, &Value_Light_Green_NowColor, &Value_Light_Green_MaxColor, &Value_Light_Green_MiniColor, Unit_Light_RGBxColor, SliderModule_NotSetting);
    MenuItem *b = Menu_CreateSliderItem(OLEDData_Icon_Blue, Name_Light_Blue, &Value_Light_Blue_NowColor, &Value_Light_Blue_MaxColor, &Value_Light_Blue_MiniColor, Unit_Light_RGBxColor, SliderModule_NotSetting);

    // 菜单项包含
    Menu_Include_MenuItem(Menu_Head_Light, state);
    Menu_Include_MenuItem(Menu_Head_Light, myauto);
    Menu_Include_MenuItem(Menu_Head_Light, r);
    Menu_Include_MenuItem(Menu_Head_Light, g);
    Menu_Include_MenuItem(Menu_Head_Light, b);
}

/**
 * @brief 创建“锁屏”菜单项
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void MyMenu_Create_MenuItem_Lock(void)
{
    // 创建菜单头
    Menu_Head_Lock = Menu_CreateMenuHead(Menu_Title_Lock);

    // 创建项
    MenuItem *state = Menu_CreateSwitchItem(OLEDData_Icon_Clock, Name_Lock_State, &State_Lock);
    MenuItem *change = Menu_CreateSliderItem(OLEDData_Icon_Image, Name_Lock_Change, &Value_Lock_NowStyle, &Value_Lock_MaxStyle, &Value_Lock_MiniStyle, Unit_Lock_Style, SliderModule_NotSetting);

    // 菜单项包含
    Menu_Include_MenuItem(Menu_Head_Lock, state);
    Menu_Include_MenuItem(Menu_Head_Lock, change);
}

/**
 * @brief 创建菜单汇总
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 建议：先创建菜单，再创建主页
 */
void MyMenu_Create_MenuItem(void)
{
    // 创建菜单项
    MyMenu_Create_MenuItem_System();
    MyMenu_Create_MenuItem_Fan();
    MyMenu_Create_MenuItem_Light();
    MyMenu_Create_MenuItem_Lock();

    // 创建主页项
    MyMenu_Create_HomeItem();
}

/**
 * @brief 计算菜单数量
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 需在创建菜单后，再计算菜单项数量
 */
void MyMenu_Calculate_MaxItem(void)
{
    // 计算菜单项
    Menu_MaxItem_System = Menu_GetMenuMaxItem(Menu_Head_System);
    Menu_MaxItem_Fan = Menu_GetMenuMaxItem(Menu_Head_Fan);
    Menu_MaxItem_Light = Menu_GetMenuMaxItem(Menu_Head_Light);
    Menu_MaxItem_Lock = Menu_GetMenuMaxItem(Menu_Head_Lock);

    // 计算主页项
    Menu_MaxItem_Home = Menu_GetHomeMaxItem(Menu_Head_Home);
}

/**
 * @brief 菜单初始化汇总
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 此函数应当在RTOS启动前调用
 * @note 如果在RTOS任务调用，会导致堆栈都空间不足
 */
void MyMenu_InitPro(void)
{
    MyMenu_Create_MenuItem();
    MyMenu_Calculate_MaxItem();
    Build_Select_NormalPage(Menu_Head_Home);
}
