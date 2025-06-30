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
    FLash_InitPro();

    /*---外件---*/
    //...

    /*---软件---*/
    MyMenu_InitPro();

    // WS2812显卡风扇灯光测试
    // WS2812_SendRGB(15, 0, 0, 0);
    // Delay_ms(100);

    // WS2812_SendRGB(12, 100, 100, 100);
    // Delay_ms(100);

    // for (uint8_t j = 0; j < 100; j += 1)
    // {
    //     WS2812_SendRGB(12, j, j, j);
    //     Delay_ms(100);
    // }

    // WS2812_SendRGB(12, 100, 0, 0);
    // Delay_ms(1000);

    // WS2812_SendRGB(12, 0, 100, 0);
    // Delay_ms(1000);

    // WS2812_SendRGB(12, 0, 0, 100);
    // Delay_ms(1000);

    /*开启任务调度*/
    TASK_InitPro();
}
