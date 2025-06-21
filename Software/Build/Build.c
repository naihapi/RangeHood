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
        KEY_RetState(KEY_NUMBER_3) == KEY_STATE_DOWNLONG) // KEY1、KEY2、KEY3、KEY4长按事件
    {
        KEY_ClearState(KEY_NUMBER_1);
        KEY_ClearState(KEY_NUMBER_2);
        KEY_ClearState(KEY_NUMBER_3);
    }
    /*~~~~~~~~~~~~无用事件~~~~~~~~~~~~*/
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

void Build_ControlPro(void)
{
    // if (Build_NowPage == 2)
    // {
    //     // 当前页：菜单页
    //     Build_MenuControl();
    // }

    if (Build_NowPage == 1)
    {
        // 当前页：主页
        Build_HomeControl();
    }
}

void Build_InitPro(void)
{
    Build_NowHomeItem = Menu_RetHomeItem(Menu_Head_Home, 1);
}
