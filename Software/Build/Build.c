#include "Build.h"

uint8_t Build_CNT_HomeItem = 1;   // 主页项计数器
uint8_t Build_CNT_MenuItem = 1;   // 菜单项计数器
uint8_t Build_CNT_SliderItem = 1; // 滑块组件选择器(1：调整当前值，2：调整最大值，3：调整最小值)
uint8_t Build_NowPage = 1;        // 当前所处页(1：主页，2：菜单页，3：组件页，4：自定义页)
MenuHome *Build_NowHomeItem;      // 当前所处主页项
MenuItem *Build_NowMenuItem;      // 当前所处菜单项

/**
 * @brief 计数目标限幅
 *
 * @param target 目标值
 * @param now 当前值
 *
 * @retval 限幅后的值
 *
 * @note 最小限幅值为1
 */
uint8_t Build_Limit(uint8_t target, uint8_t now)
{
    if (now > target)
    {
        return target;
    }
    else if (now <= 0)
    {
        return 1;
    }
    else
    {
        return now;
    }
}

/**
 * @brief 设置标志位/计数器的数值
 *
 * @param value 设置的变量地址
 * @param target 目标值(BUILD_SV_xxx)
 *
 * @retval 无
 *
 * @note 无
 */
void Build_SetValue(uint8_t *value, int32_t target)
{
    *value = target;
}

/**
 * @brief 主页按键事件
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 主页的按键控制逻辑汇总
 */
void Build_HomeControl_KEYevent(void)
{
    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/
    if (KEY_RetState(KEY_NUMBER_1) == KEY_STATE_DOWNSHORT) // KEY1短按事件-确认
    {
        Build_SetValue(&Build_NowPage, BUILD_SV_NOWPAGE_MENU);                             // 切换到菜单页
        Build_NowMenuItem = Menu_RetMenuItem(Build_NowHomeItem->Menu, Build_CNT_MenuItem); // 更新当前菜单项

        KEY_ClearState(KEY_NUMBER_1);
    }
    if (KEY_RetState(KEY_NUMBER_2) == KEY_STATE_DOWNSHORT) // KEY2短按事件-上一项
    {
        Build_CNT_HomeItem--;                                                    // 主页项减少1
        Build_CNT_HomeItem = Build_Limit(Menu_MaxItem_Home, Build_CNT_HomeItem); // 限幅

        Build_NowHomeItem = Menu_RetHomeItem(Menu_Head_Home, Build_CNT_HomeItem); // 更新当前主页项

        KEY_ClearState(KEY_NUMBER_2);
    }
    if (KEY_RetState(KEY_NUMBER_3) == KEY_STATE_DOWNSHORT) // KEY3短按事件-下一项
    {
        Build_CNT_HomeItem++;                                                    // 主页项增加1
        Build_CNT_HomeItem = Build_Limit(Menu_MaxItem_Home, Build_CNT_HomeItem); // 限幅

        Build_NowHomeItem = Menu_RetHomeItem(Menu_Head_Home, Build_CNT_HomeItem); // 更新当前主页项

        KEY_ClearState(KEY_NUMBER_3);
    }
    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/

    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
    if (KEY_RetState(KEY_NUMBER_1) == KEY_STATE_DOWNLONG ||
        KEY_RetState(KEY_NUMBER_2) == KEY_STATE_DOWNLONG ||
        KEY_RetState(KEY_NUMBER_3) == KEY_STATE_DOWNLONG) // KEY1、KEY2、KEY3长按事件
    {
        KEY_ClearState(KEY_NUMBER_1);
        KEY_ClearState(KEY_NUMBER_2);
        KEY_ClearState(KEY_NUMBER_3);
    }
    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
}

/**
 * @brief 菜单页面按键事件
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 菜单的按键控制逻辑汇总
 */
void Build_MenuControl_KEYevent(void)
{
    int8_t *maxitem = Build_NowHomeItem->MaxItem; // 获取最大项

    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/
    if (KEY_RetState(KEY_NUMBER_1) == KEY_STATE_DOWNSHORT) // KEY1短按事件
    {
        // 切换页面，需重写。。。
        Build_SetValue(&Build_NowPage, BUILD_SV_NOWPAGE_MODULE);

        KEY_ClearState(KEY_NUMBER_1);
    }
    if (KEY_RetState(KEY_NUMBER_1) == KEY_STATE_DOWNLONG) // KEY1长按事件
    {
        Build_SetValue(&Build_NowPage, BUILD_SV_NOWPAGE_HOME); // 返回主页
        Build_SetValue(&Build_CNT_MenuItem, 1);                // 菜单项计数初始化

        KEY_ClearState(KEY_NUMBER_1);
    }
    if (KEY_RetState(KEY_NUMBER_2) == KEY_STATE_DOWNSHORT) // KEY2短按事件
    {
        Build_CNT_MenuItem--;                                           // 主页项减少1
        Build_CNT_MenuItem = Build_Limit(*maxitem, Build_CNT_MenuItem); // 限幅

        Build_NowMenuItem = Menu_RetMenuItem(Build_NowHomeItem->Menu, Build_CNT_MenuItem); // 更新当前菜单项

        KEY_ClearState(KEY_NUMBER_2);
    }
    if (KEY_RetState(KEY_NUMBER_3) == KEY_STATE_DOWNSHORT) // KEY3短按事件
    {
        Build_CNT_MenuItem++;                                           // 主页项增加1
        Build_CNT_MenuItem = Build_Limit(*maxitem, Build_CNT_MenuItem); // 限幅

        Build_NowMenuItem = Menu_RetMenuItem(Build_NowHomeItem->Menu, Build_CNT_MenuItem); // 更新当前菜单项

        KEY_ClearState(KEY_NUMBER_3);
    }
    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/

    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
    if (KEY_RetState(KEY_NUMBER_1) == KEY_STATE_DOWNLONG ||
        KEY_RetState(KEY_NUMBER_2) == KEY_STATE_DOWNLONG ||
        KEY_RetState(KEY_NUMBER_3) == KEY_STATE_DOWNLONG)
    {
        KEY_ClearState(KEY_NUMBER_1);
        KEY_ClearState(KEY_NUMBER_2);
        KEY_ClearState(KEY_NUMBER_3);
    }
    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
}

/**
 * @brief 开关组件按键事件
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 开关组件可以切换状态，退出组件需要进入上传页
 */
void Build_ModuleControl_Switch_KEYevent(void)
{
    Menu_SwitchModule *switchmodule = Build_NowMenuItem->ItemPointer; // 获取菜单项指向的开关组件
    uint8_t *state = switchmodule->State;                             // 获取开关组件的当前状态

    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/
    if (KEY_RetState(KEY_NUMBER_1) == KEY_STATE_DOWNLONG) // KEY1长按事件-返回菜单
    {
        Build_SetValue(&Build_NowPage, BUILD_SV_NOWPAGE_MENU);

        KEY_ClearState(KEY_NUMBER_1);
    }
    if (KEY_RetState(KEY_NUMBER_2) == KEY_STATE_DOWNLONG) // KEY2长按事件-打开
    {
        Build_SetValue(state, 1); // 打开

        KEY_ClearState(KEY_NUMBER_2);
    }
    if (KEY_RetState(KEY_NUMBER_3) == KEY_STATE_DOWNLONG) // KEY3长按事件-关闭
    {
        Build_SetValue(state, 0);

        KEY_ClearState(KEY_NUMBER_3);
    }
    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/

    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
    if (KEY_RetState(KEY_NUMBER_2) == KEY_STATE_DOWNSHORT ||
        KEY_RetState(KEY_NUMBER_3) == KEY_STATE_DOWNSHORT)
    {
        KEY_ClearState(KEY_NUMBER_2);
        KEY_ClearState(KEY_NUMBER_3);
    }
    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
}

/**
 * @brief 视图组件按键事件
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 视图组件只用于查看数据，不需要进入上传页
 */
void Build_ModuleControl_View_KEYevent(void)
{
    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/
    if (KEY_RetState(KEY_NUMBER_1) == KEY_STATE_DOWNLONG) // KEY1长按事件-返回菜单
    {
        Build_SetValue(&Build_NowPage, BUILD_SV_NOWPAGE_MENU); // 切换到菜单页

        KEY_ClearState(KEY_NUMBER_2);
    }
    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/

    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
    if (KEY_RetState(KEY_NUMBER_1) == KEY_STATE_DOWNSHORT ||
        KEY_RetState(KEY_NUMBER_2) == KEY_STATE_DOWNSHORT ||
        KEY_RetState(KEY_NUMBER_3) == KEY_STATE_DOWNSHORT)
    {
        KEY_ClearState(KEY_NUMBER_1);
        KEY_ClearState(KEY_NUMBER_2);
        KEY_ClearState(KEY_NUMBER_3);
    }
    if (KEY_RetState(KEY_NUMBER_2) == KEY_STATE_DOWNLONG ||
        KEY_RetState(KEY_NUMBER_3) == KEY_STATE_DOWNLONG)
    {
        KEY_ClearState(KEY_NUMBER_2);
        KEY_ClearState(KEY_NUMBER_3);
    }
    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
}

/**
 * @brief 滑块组件按键减少数值事件
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 根据当前停留的项(now max mini)，增加数值
 */
void Build_ModuleControl_Slider_KEYevent_REDUCE(void)
{
    Menu_SliderModule *slidermodule = Build_NowMenuItem->ItemPointer;
    int *now = slidermodule->NowValue;
    int *max = slidermodule->MaxValue;
    int *mini = slidermodule->MiniValue;

    switch (Build_CNT_SliderItem)
    {
    case 1:
    {
        *now -= 1; // 增加数值

        if (*now < *mini) // 限幅
        {
            *now += 1;
        }
    }
    break;

    case 2:
    {
        *max -= 1; // 减少数值

        if (*max < *now) // 限幅
        {
            *max += 1;
        }
    }
    break;

    case 3:
    {
        *mini -= 1;
    }
    break;
    }
}

/**
 * @brief 滑块组件按键增加数值事件
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 根据当前停留的项(now max mini)，增加数值
 */
void Build_ModuleControl_Slider_KEYevent_INCREASE(void)
{
    Menu_SliderModule *slidermodule = Build_NowMenuItem->ItemPointer;
    int *now = slidermodule->NowValue;
    int *max = slidermodule->MaxValue;
    int *mini = slidermodule->MiniValue;

    switch (Build_CNT_SliderItem)
    {
    case 1:
    {
        *now += 1; // 增加数值

        // 限幅
        if (*now > *max)
        {
            *now -= 1;
        }
    }
    break;

    case 2:
    {
        *max += 1; // 增加数值
    }
    break;

    case 3:
    {
        *mini += 1; // 增加数值

        if (*mini > *now)
        {
            *mini -= 1;
        }
    }
    break;
    }
}

/**
 * @brief 滑块组件按键事件
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Build_ModuleControl_Slider_KEYevent(void)
{
    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/
    if (KEY_RetState(KEY_NUMBER_1) == KEY_STATE_DOWNLONG) // KEY1长按事件-返回菜单
    {
        Build_SetValue(&Build_NowPage, BUILD_SV_NOWPAGE_MENU); // 切换到菜单页

        KEY_ClearState(KEY_NUMBER_1); // 清除状态
    }
    if (KEY_RetState(KEY_NUMBER_2) == KEY_STATE_DOWNSHORT) // KEY2短按事件-减少数值
    {
        Build_ModuleControl_Slider_KEYevent_REDUCE();

        KEY_ClearState(KEY_NUMBER_2); // 清除状态
    }
    if (KEY_RetState(KEY_NUMBER_3) == KEY_STATE_DOWNSHORT) // KEY3短按事件-增加数值
    {
        Build_ModuleControl_Slider_KEYevent_INCREASE();

        KEY_ClearState(KEY_NUMBER_3); // 清除状态
    }
    if (KEY_RetState(KEY_NUMBER_2) == KEY_STATE_DOWNLONG) // KEY2长按事件-滑块项减少(now|max|mini)
    {
        // 获取是否可以切换滑块项的权限
        Menu_SliderModule *nowslider = Build_NowMenuItem->ItemPointer;
        uint8_t setting = nowslider->Setting;
        if (setting == SliderModule_NotSetting)
        {
        }
        else
        {
            Build_CNT_SliderItem--;                                      // 更新选中项
            Build_CNT_SliderItem = Build_Limit(3, Build_CNT_SliderItem); // 限幅
        }

        KEY_ClearState(KEY_NUMBER_2); // 清除状态
    }
    if (KEY_RetState(KEY_NUMBER_3) == KEY_STATE_DOWNLONG) // KEY3长按事件-滑块项增加(now|max|mini)
    {
        // 获取是否可以切换滑块项的权限
        Menu_SliderModule *nowslider = Build_NowMenuItem->ItemPointer;
        uint8_t setting = nowslider->Setting;
        if (setting == SliderModule_NotSetting)
        {
        }
        else
        {
            Build_CNT_SliderItem++;                                      // 更新选中项
            Build_CNT_SliderItem = Build_Limit(3, Build_CNT_SliderItem); // 限幅
        }

        KEY_ClearState(KEY_NUMBER_3); // 清除状态
    }
    /*~~~~~~~~~~~~有用事件~~~~~~~~~~~~*/

    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
    if (KEY_RetState(KEY_NUMBER_1) == KEY_STATE_DOWNSHORT)
    {
        KEY_ClearState(KEY_NUMBER_1);
    }
    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
}

/**
 * @brief 组件按键事件
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 组件的按键控制逻辑汇总
 * @note 每个组件对应的按键事件都不一样，需要各写一个函数
 */
void Build_ModuleControl_KEYevent(void)
{
    uint8_t moduletype = Build_NowMenuItem->ItemType; // 获取当前组件类型

    switch (moduletype)
    {
    case ItemType_Switch:
        Build_ModuleControl_Switch_KEYevent();
        break;
    case ItemType_View:
        Build_ModuleControl_View_KEYevent();
        break;
    case ItemType_Slider:
        Build_ModuleControl_Slider_KEYevent();
        break;
    }
}

/**
 * @brief 组件控制选择性显示
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 组件控制的选择其一组件显示，取决于当前组件类型
 * @note 如果创建菜单项时，打开了实时活动，此时会：请求1次数据/500ms（仅支持视图型组件）
 */
void Build_ModuleControl_SelectDisplay(void)
{
    uint8_t module = Build_NowMenuItem->ItemType; // 获取当前菜单的组件类型

    switch (module)
    {
    case ItemType_Switch:
    {
        Menu_SwitchModule *switchmodule = Build_NowMenuItem->ItemPointer; // 创建对象，对象指向当前菜单
        uint8_t *state = switchmodule->State;                             // 状态

        UI_Display_SwitchModule(Build_NowMenuItem->Title, state); // 渲染开关组件
    }
    break;

    case ItemType_View:
    {
        Menu_ViewModule *viewmodule = Build_NowMenuItem->ItemPointer; // 创建对象，对象指向当前菜单
        int value = *viewmodule->Value;                               // 数值

        UI_Display_ViewModule(Build_NowMenuItem->Title, viewmodule->Description, &value); // 渲染视图组件
    }
    break;

    case ItemType_Slider:
    {
        Menu_SliderModule *slidermodule = Build_NowMenuItem->ItemPointer; // 创建对象，对象指向当前菜单
        int nowvalue = *slidermodule->NowValue;                           // 当前值
        int maxvalue = *slidermodule->MaxValue;                           // 最大值
        int minivalue = *slidermodule->MiniValue;                         // 最小值
        uint8_t *unit = slidermodule->Unit;

        UI_Display_SliderModule(Build_NowMenuItem->Title, &nowvalue, &maxvalue, &minivalue, unit, Build_CNT_SliderItem); // 渲染滑块组件
    }
    break;
    }
}

/**
 * @brief 主页控制
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Build_HomeControl(void)
{
    // 主页按键控制
    Build_HomeControl_KEYevent();

    // 主页渲染
    UI_Display_Home(Build_CNT_HomeItem, Menu_Head_Home);
}

/**
 * @brief 菜单页控制
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Build_MenuControl(void)
{
    // 菜单按键控制
    Build_MenuControl_KEYevent();

    // 获取当前主页项和最大项
    MenuItem *current = Build_NowHomeItem->Menu;
    int8_t *maxitem = Build_NowHomeItem->MaxItem;

    // 菜单渲染
    UI_Display_Menu(Build_CNT_MenuItem, current, *maxitem);
}

/**
 * @brief 组件控制
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Build_ModuleControl(void)
{
    // 组件按键控制
    Build_ModuleControl_KEYevent();

    // 组件渲染
    Build_ModuleControl_SelectDisplay();
}

/**
 * @brief 页面构建汇总
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Build_ControlPro(void)
{
    if (Build_NowPage == BUILD_SV_NOWPAGE_MENU)
    {
        // 当前页：菜单页
        Build_MenuControl();
    }

    if (Build_NowPage == BUILD_SV_NOWPAGE_HOME)
    {
        // 当前页：主页
        Build_HomeControl();
    }

    if (Build_NowPage == BUILD_SV_NOWPAGE_MODULE)
    {
        // 当前页：组件页
        Build_ModuleControl();
    }
}

/**
 * @brief 页面构建初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Build_InitPro(void)
{
    // 选定默认页
    Build_NowHomeItem = Menu_RetHomeItem(Menu_Head_Home, 1);
}
