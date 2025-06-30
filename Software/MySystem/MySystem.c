#include "MySystem.h"

WS2812_t MySystem_WS2812_Buffer[MYSYSTEM_WS2812_NUMBER];
uint8_t MySystem_Fanlight_GradualChange_Same_Red_Flag = MYSYSTEM_WS2812_GC_INCREASE;   // MYSYSTEM_WS2812_GC_xxx
uint8_t MySystem_Fanlight_GradualChange_Same_Green_Flag = MYSYSTEM_WS2812_GC_INCREASE; // MYSYSTEM_WS2812_GC_xxx
uint8_t MySystem_Fanlight_GradualChange_Same_Blue_Flag = MYSYSTEM_WS2812_GC_INCREASE;  // MYSYSTEM_WS2812_GC_xxx

void MySystem_InitPro(void)
{
}

/**
 * @brief OLED深浅模式配置
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void MySystem_OLED_DarkColor(void)
{
    switch (State_OLEDMode)
    {
    case 0:
        // 深色模式
        OLED_WriteCommand(0xA6);
        break;

    case 1:
        // 浅色模式
        OLED_WriteCommand(0xA7);
        break;
    }
}

/**
 * @brief OLED亮度配置
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void MySystem_OLED_Brightness(void)
{
    switch (Value_OLED_NowBrightness)
    {
    case 1:
        // 亮度暗
        OLED_WriteCommand(0x81);
        OLED_WriteCommand(0x01);
        break;

    case 2:
        // 亮度中等
        OLED_WriteCommand(0x81);
        OLED_WriteCommand(0x32);
        break;

    case 3:
        // 亮度高
        OLED_WriteCommand(0x81);
        OLED_WriteCommand(0xFF);
        break;
    }
}

/**
 * @brief OLED左右方向配置
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void MySystem_OLED_DirectionLR(void)
{
    switch (State_OLEDDirection_LR)
    {
    case 0:
        // 正常
        OLED_WriteCommand(0xA1);
        break;

    case 1:
        // 反置
        OLED_WriteCommand(0xA0);
        break;
    }
}

/**
 * @brief OLED上下方向配置
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void MySystem_OLED_DirectionTB(void)
{
    switch (State_OLEDDirection_TB)
    {
    case 0:
        // 正常
        OLED_WriteCommand(0xC8);
        break;

    case 1:
        // 反置
        OLED_WriteCommand(0xC0);
        break;
    }
}

/**
 * @brief OLED控制函数
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 在OLED.c文件的Update函数内调用
 */
void MySystem_OLED_Function(void)
{
    MySystem_OLED_DarkColor();
    MySystem_OLED_Brightness();
    MySystem_OLED_DirectionLR();
    MySystem_OLED_DirectionTB();
}

/**
 * @brief 获取RTOS的剩余堆空间
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 此函数需要全速运行
 */
void MySystem_GetFreeHeap(void)
{
    Value_FreeHeap = xPortGetFreeHeapSize();
}

/**
 * @brief 灯光颜色更新
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 调用函数将短暂进入临界区
 */
void MySystem_Fanlight_Update(void)
{
    taskENTER_CRITICAL();

    for (uint8_t i = 0; i < MYSYSTEM_WS2812_NUMBER; i++)
    {
        WS2812_SendRGB(i, MySystem_WS2812_Buffer[i].Red,
                       MySystem_WS2812_Buffer[i].Green,
                       MySystem_WS2812_Buffer[i].Blue);
    }

    taskEXIT_CRITICAL();
}

/**
 * @brief 设置灯光颜色
 *
 * @param Red 红色
 * @param Green 绿色
 * @param Blue 蓝色
 *
 * @retval 无
 *
 * @note 无
 */
void MySystem_Fanlight_SetColor(uint8_t Red, uint8_t Green, uint8_t Blue)
{

    for (uint8_t i = 0; i < MYSYSTEM_WS2812_NUMBER; i++)
    {
        MySystem_WS2812_Buffer[i].Red = Red;
        MySystem_WS2812_Buffer[i].Green = Green;
        MySystem_WS2812_Buffer[i].Blue = Blue;
    }
}

/**
 * @brief 同色渐变初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void MySystem_Fanlight_GradualChange_Same_Init(void)
{
    for (uint8_t i = 0; i < MYSYSTEM_WS2812_NUMBER; i++)
    {
        MySystem_WS2812_Buffer[i].Red = 150;
        MySystem_WS2812_Buffer[i].Green = 50;
        MySystem_WS2812_Buffer[i].Blue = 250;
    }
}

/**
 * @brief 同色渐变
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 所有灯珠的单项色都相同
 */
void MySystem_Fanlight_GradualChange_Same(void)
{
    uint8_t step = 1;  // 步长
    uint8_t max = 250; // 最大值
    uint8_t mini = 5;  // 最小值

    for (uint8_t j = 0; j < MYSYSTEM_WS2812_NUMBER; j++)
    {
        // Red渐变
        if (MySystem_Fanlight_GradualChange_Same_Red_Flag == MYSYSTEM_WS2812_GC_INCREASE)
        {
            MySystem_WS2812_Buffer[j].Red += step;    // 数值增加
            if (MySystem_WS2812_Buffer[j].Red >= max) // 限幅和调换
            {
                MySystem_Fanlight_GradualChange_Same_Red_Flag = MYSYSTEM_WS2812_GC_REDUCE;
            }
        }
        if (MySystem_Fanlight_GradualChange_Same_Red_Flag == MYSYSTEM_WS2812_GC_REDUCE)
        {
            MySystem_WS2812_Buffer[j].Red -= step;     // 数值减少
            if (MySystem_WS2812_Buffer[j].Red <= mini) // 限幅和调换
            {
                MySystem_Fanlight_GradualChange_Same_Red_Flag = MYSYSTEM_WS2812_GC_INCREASE;
            }
        }

        // Green渐变
        if (MySystem_Fanlight_GradualChange_Same_Green_Flag == MYSYSTEM_WS2812_GC_INCREASE)
        {
            MySystem_WS2812_Buffer[j].Green += step;    // 数值增加
            if (MySystem_WS2812_Buffer[j].Green >= max) // 限幅和调换
            {
                MySystem_Fanlight_GradualChange_Same_Green_Flag = MYSYSTEM_WS2812_GC_REDUCE;
            }
        }
        if (MySystem_Fanlight_GradualChange_Same_Green_Flag == MYSYSTEM_WS2812_GC_REDUCE)
        {
            MySystem_WS2812_Buffer[j].Green -= step;     // 数值减少
            if (MySystem_WS2812_Buffer[j].Green <= mini) // 限幅和调换
            {
                MySystem_Fanlight_GradualChange_Same_Green_Flag = MYSYSTEM_WS2812_GC_INCREASE;
            }
        }

        // Blue渐变
        if (MySystem_Fanlight_GradualChange_Same_Blue_Flag == MYSYSTEM_WS2812_GC_INCREASE)
        {
            MySystem_WS2812_Buffer[j].Blue += step;    // 数值增加
            if (MySystem_WS2812_Buffer[j].Blue >= max) // 限幅和调换
            {
                MySystem_Fanlight_GradualChange_Same_Blue_Flag = MYSYSTEM_WS2812_GC_REDUCE;
            }
        }
        if (MySystem_Fanlight_GradualChange_Same_Blue_Flag == MYSYSTEM_WS2812_GC_REDUCE)
        {
            MySystem_WS2812_Buffer[j].Blue -= step;     // 数值减少
            if (MySystem_WS2812_Buffer[j].Blue <= mini) // 限幅和调换
            {
                MySystem_Fanlight_GradualChange_Same_Blue_Flag = MYSYSTEM_WS2812_GC_INCREASE;
            }
        }

        MySystem_Fanlight_SetColor(MySystem_WS2812_Buffer[j].Red,
                                   MySystem_WS2812_Buffer[j].Green,
                                   MySystem_WS2812_Buffer[j].Blue);
    }
}

/**
 * @brief 异色渐变初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 由于所有灯珠的单项色都不相同
 * @note 因此需要随机数分配RGB颜色
 */
void MySystem_Fanlight_GradualChange_Different_Init(void)
{
}

/**
 * @brief 异色渐变
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 所有灯珠的单项色都不相同
 * @note 使用前需调用1次xxx_Different_Init函数
 */
void MySystem_Fanlight_GradualChange_Different(void)
{
}

/**
 * @brief 风扇转速控制
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 档位控制1:20
 */
void MySystem_FanSpeed_Function(void)
{
    if (!State_Fan)
    {
        TIM_FAN_SetDuty(0);
    }
    else
    {
        TIM_FAN_SetDuty(Value_Fan_NowSpeed * 20);
    }
}
