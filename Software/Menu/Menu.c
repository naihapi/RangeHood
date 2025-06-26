#include "Menu.h"

/**
 * @brief 创建1个主页项
 *
 * @param icon 图标
 * @param title 标题
 * @param menu 菜单链表头
 * @param maxitem 菜单最大个数
 *
 * @retval 返回主页项
 * @retval 创建失败返回NULL
 *
 * @note 分配内存以创建主页项
 * @note 由于创建链表头时无数据传入，因此不检查函数参数
 */
MenuHome *Menu_CreateHomeItem(const uint8_t *icon, uint8_t *title, MenuItem *menu, int8_t *maxitem)
{
    // 为<主页结构体>分配内存
    MenuHome *Item = (MenuHome *)malloc(sizeof(MenuHome));
    if (Item == NULL)
        return NULL;

    Item->Icon = icon;       // 图标
    Item->Title = title;     // 标题
    Item->Menu = menu;       // 菜单
    Item->MaxItem = maxitem; // 最大项

    // Menu_MaxItem_Home += 1;

    return Item;
}

/**
 * @brief 创建1个菜单项
 *
 * @param icon 图标
 * @param title 标题
 * @param type 菜单类型：ItemType_xxx
 * @param function 自定义函数
 * @param pointer 具体组件：Menu_xxxModule
 * @param name 硬件名称
 *
 * @retval 返回1个菜单项
 * @retval 创建失败返回NULL
 *
 * @note <菜单结构体>的<标题Title>和<名称name>取决于<函数参数name>
 */
MenuItem *Menu_CreateItem(const uint8_t *icon, uint8_t type, void *function, void *pointer, uint8_t *name)
{
    // 为<菜单结构体>分配内存
    MenuItem *Item = (MenuItem *)malloc(sizeof(MenuItem));
    if (Item == NULL)
        return NULL;

    Item->Icon = icon;           // 图标
    Item->Title = name;          // 标题取决于硬件名称
    Item->ItemType = type;       // 组件类型
    Item->Function = function;   // 函数
    Item->ItemPointer = pointer; // 组件数据
    Item->Name = name;           // 名称

    return Item;
}

/**
 * @brief 创建1个开关型组件
 *
 * @param state 开关状态
 *
 * @retval 返回1个开关组件
 * @retval 创建失败返回NULL
 *
 * @note 无
 */
Menu_SwitchModule *Mneu_CreateSwitchModule(uint8_t *state)
{
    // 为<开关型组件结构体>分配内存
    Menu_SwitchModule *SwitchData = (Menu_SwitchModule *)malloc(sizeof(Menu_SwitchModule));
    if (SwitchData == NULL)
        return NULL;

    SwitchData->State = state; // 开关状态

    return SwitchData;
}

/**
 * @brief 创建1个视图型组件
 *
 * @param description 描述信息
 * @param value 数值
 *
 * @retval 返回1个视图组件
 * @retval 创建失败返回NULL
 *
 * @note 无
 */
Menu_ViewModule *Menu_CreateViewModule(uint8_t *description, int *value)
{
    // 为<视图型组件结构体>分配内存
    Menu_ViewModule *ViewData = (Menu_ViewModule *)malloc(sizeof(Menu_ViewModule));
    if (ViewData == NULL)
        return NULL;

    ViewData->Description = description; // 信息描述
    ViewData->Value = value;             // 数据值

    return ViewData;
}

/**
 * @brief 创建1个滑块型组件
 *
 * @param nowvalue 描述信息
 * @param maxvalue 最大值
 * @param minivalue 最小值
 * @param setting 调整限幅值(SliderModule_xxxSetting)
 * @param unit 单位
 *
 * @retval 返回1个滑块组件
 * @retval 创建失败返回NULL
 *
 * @note 无
 */
Menu_SliderModule *Menu_CreateSliderModule(int *nowvalue, int *maxvalue, int *minivalue, uint8_t setting, uint8_t *unit)
{
    // 为<滑块型组件结构体>分配内存
    Menu_SliderModule *SliderData = (Menu_SliderModule *)malloc(sizeof(Menu_SliderModule));
    if (SliderData == NULL)
        return NULL;

    SliderData->NowValue = nowvalue;   // 当前值
    SliderData->MaxValue = maxvalue;   // 最大值
    SliderData->MiniValue = minivalue; // 最小值
    SliderData->Setting = setting;     // 限幅设置
    SliderData->Unit = unit;

    return SliderData;
}

/**
 * @brief 创建1个开关型菜单项
 *
 * @param icon 图标
 * @param name 硬件名称
 * @param state 状态(1或0)
 * @param datahandle 数据处理标志位：DataHandle_xxx
 *
 * @retval 返回1个开关型菜单项
 * @retval 创建失败返回NULL
 *
 * @note <菜单结构体>和<开关型组件结构体>的结构体创建都在此函数完成
 */
MenuItem *Menu_CreateSwitchItem(const uint8_t *icon, uint8_t *name, uint8_t *state)
{
    // 创建<开关型组件结构体>
    Menu_SwitchModule *SwitchData = Mneu_CreateSwitchModule(state);
    if (SwitchData == NULL)
        return NULL;

    // 创建<菜单结构体>
    MenuItem *Item = Menu_CreateItem(icon, ItemType_Switch, NULL, SwitchData, name);
    if (SwitchData == NULL)
        return NULL;

    return Item;
}

/**
 * @brief 创建1个视图型菜单项
 *
 * @param icon 图标
 * @param name 硬件名称
 * @param description 描述符
 * @param value 数值
 * @param datahandle 数据处理标志位：DataHandle_xxx
 * @param realtime 实时活动标志位：ViewModule_DataRealTime_xxx
 *
 * @retval 返回1个视图型菜单项
 * @retval 创建失败返回NULL
 *
 * @note <菜单结构体>和<视图型组件结构体>的结构体创建都在此函数完成
 */
MenuItem *Menu_CreateViewItem(const uint8_t *icon, uint8_t *name, uint8_t *description, int *value)
{
    // 创建<视图型组件结构体>
    Menu_ViewModule *ViewData = Menu_CreateViewModule(description, value);
    if (ViewData == NULL)
        return NULL;

    // 创建<菜单结构体>
    MenuItem *Item = Menu_CreateItem(icon, ItemType_View, NULL, ViewData, name);
    if (Item == NULL)
        return NULL;

    return Item;
}

/**
 * @brief 创建1个滑块型菜单项
 *
 * @param icon 图标
 * @param name 硬件名称
 * @param nowvalue 当前值
 * @param maxvalue 最大值
 * @param minivalue 最小值
 * @param unit 单位
 * @param setting 调整限幅值(SliderModule_xxxSetting)
 * @param datahandle 数据处理标志位：DataHandle_xxx
 *
 * @retval 返回1个视图型菜单项
 * @retval 创建失败返回NULL
 *
 * @note <菜单结构体>和<视图型组件结构体>的结构体创建都在此函数完成
 */
MenuItem *Menu_CreateSliderItem(const uint8_t *icon, uint8_t *name, int *nowvalue, int *maxvalue, int *minivalue, uint8_t *unit, uint8_t setting)
{
    // 创建<滑块型组件结构体>
    Menu_SliderModule *SliderData = Menu_CreateSliderModule(nowvalue, maxvalue, minivalue, setting, unit);
    if (SliderData == NULL)
        return NULL;

    // 创建<菜单结构体>
    MenuItem *Item = Menu_CreateItem(icon, ItemType_Slider, NULL, SliderData, name);
    if (Item == NULL)
        return NULL;

    return Item;
}

/**
 * @brief 创建1个自定义型菜单项
 *
 * @param icon 图标
 * @param name 名称
 * @param function 函数
 *
 * @retval 返回1个自定义型菜单项
 * @retval 创建失败返回NULL
 *
 * @note function参数为函数地址，函数返回值为void
 * @note <菜单结构体>的结构体创建都在此函数完成
 */
MenuItem *Menu_CreateCustomItem(const uint8_t *icon, uint8_t *name, void *function)
{
    // 创建<菜单结构体>
    MenuItem *Item = Menu_CreateItem(icon, ItemType_Custom, function, NULL, name);
    if (Item == NULL)
        return NULL;

    return Item;
}

/**
 * @brief 获取指定的主页项
 *
 * @param Head 主页链表头
 * @param item 选择的项(从1开始)
 *
 * @retval 返回指定项
 * @retval 获取失败返回NULL
 *
 * @note 已跳过头节点
 */
MenuHome *Menu_RetHomeItem(MenuHome *Head, uint8_t item)
{
    if (Head == NULL || item <= 0)
        return NULL;

    uint8_t count = 1;              // 查询主页项计数
    MenuHome *current = Head->Next; // 跳过头节点

    // 遍历链表
    while (current != NULL)
    {
        if (item == count)
        {
            return current;
        }

        count++;                 // 计数自增，直到与item相等
        current = current->Next; // 查询下一项
    }
    return 0;
}

/**
 * @brief 获取指定的菜单项
 *
 * @param Head 菜单链表头
 * @param item 选择的项(从1开始)
 *
 * @retval 返回指定项
 * @retval 获取失败返回NULL
 *
 * @note 已跳过头节点
 */
MenuItem *Menu_RetMenuItem(MenuItem *Head, uint8_t item)
{
    if (Head == NULL || item <= 0)
        return NULL;

    uint8_t count = 1;              // 查询菜单项计数
    MenuItem *current = Head->Next; // 跳过头节点

    // 遍历链表
    while (current != NULL)
    {
        if (item == count)
        {
            return current;
        }

        count++;                 // 计数自增，直到与item相等
        current = current->Next; // 查询下一项
    }

    return NULL;
}

/**
 * @brief 获取主页最大项
 *
 * @param head 主页链表头
 *
 * @retval 返回菜单个数
 *
 * @note 无
 */
int8_t Menu_GetHomeMaxItem(MenuHome *head)
{
    int8_t maxitem = 0;
    MenuHome *current = head->Next; // 从头节点的下一个节点开始计数

    while (current != NULL)
    {
        maxitem += 1;
        current = current->Next;
    }

    return maxitem;
}

/**
 * @brief 获取菜单最大项
 *
 * @param head 菜单链表头
 *
 * @retval 返回菜单个数
 *
 * @note 无
 */
int8_t Menu_GetMenuMaxItem(MenuItem *head)
{
    int8_t maxitem = 0;
    MenuItem *current = head->Next; // 从头节点的下一个节点开始计数

    while (current != NULL)
    {
        maxitem += 1;
        current = current->Next;
    }

    return maxitem;
}

/**
 * @brief 获取主页最后一项
 *
 * @param head 主页链表头
 *
 * @retval 返回主页项
 *
 * @note 无
 */
MenuHome *Menu_GetHomeEndItem(MenuHome *head)
{
    MenuHome *current = head;

    while (current->Next != NULL)
    {
        current = current->Next;
    }

    return current;
}

/**
 * @brief 获取菜单最后一项
 *
 * @param head 菜单链表头
 *
 * @retval 返回菜单项
 *
 * @note 无
 */
MenuItem *Menu_GetMenuEndItem(MenuItem *head)
{
    MenuItem *current = head;

    while (current->Next != NULL)
    {
        current = current->Next;
    }

    return current;
}

/**
 * @brief 菜单项互指
 *
 * @param nowitem 当前项
 * @param lastitem 上一项
 * @param nextitem 下一项
 *
 * @retval 无
 *
 * @note 小记：双指针是指向指针的指针
 * @note 利用双指针，改变单指针所指向的地方
 * @note 互指：上一项的Next指向下一项，下一项的Last指向上一项
 */
void Menu_ItemEachOther(MenuItem **nowitem, MenuItem *lastitem, MenuItem *nextitem)
{
    (*nowitem)->Next = nextitem;
    (*nowitem)->Last = lastitem;
}

/**
 * @brief 主页项包含到主页头
 *
 * @param head 主页链表头
 * @param item 主页项
 *
 * @retval 无
 *
 * @note 无
 */
void Menu_Include_HomeItem(MenuHome *head, MenuHome *item)
{
    MenuHome *current = Menu_GetHomeEndItem(head);

    current->Next = item;
    item->Last = current;
    item->Next = NULL;
}

/**
 * @brief 菜单项包含到菜单头
 *
 * @param head 菜单链表头
 * @param item 菜单项
 *
 * @retval 无
 *
 * @note 无
 */
void Menu_Include_MenuItem(MenuItem *head, MenuItem *item)
{
    MenuItem *current = Menu_GetMenuEndItem(head);

    current->Next = item;
    item->Last = current;
    item->Next = NULL;
}

/**
 * @brief 创建一个主页头
 *
 * @param 无
 *
 * @retval 返回主页头
 *
 * @note 无
 */
MenuHome *Menu_CreateHomeHead(void)
{
    MenuHome *Head = Menu_CreateHomeItem(NULL, NULL, NULL, NULL);
    return Head;
}

/**
 * @brief 创建一个菜单头
 *
 * @param title 菜单标题
 *
 * @retval 返回菜单头
 *
 * @note 无
 */
MenuItem *Menu_CreateMenuHead(uint8_t *title)
{
    MenuItem *Head = Menu_CreateItem(NULL, NULL, NULL, NULL, title);
    return Head;
}
