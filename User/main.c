#include "main.h"

/**
 * @brief main主函数
 *
 * @param WechatSupport naihapi
 *
 * @note 外设：MCU外设初始化函数
 * @note 外件：外部传感器等
 * @note TASK1附带LED测试灯 LED-PB8
 */
int main(void)
{
    /*---外设---*/
    GPIO_InitPro();
    TIM_InitPro();
    TIM_SetCompare2(TIM1, 10);

    /*---外件---*/
    //...

    /*---软件---*/
    //...

    WS2812_SendRGB(10, 0, 0, 0);
    Delay_ms(100);

    for (uint8_t i = 1; i < 11; i++)
    {
        WS2812_SendRGB(i, 100, 100, 100);
        Delay_ms(1000);
    }

    /*开启任务调度*/
    TASK_InitPro();
}
