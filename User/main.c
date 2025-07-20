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

    RCC_DeInit();
    RCC_HSEConfig(RCC_HSE_ON);
    while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET)
        ;

    // 配置PLL：假设HSE=8MHz，PLL倍频为9 -> 8 * 9=72MHz
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
    RCC_PLLCmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        ;

    // 设置系统时钟源为PLL
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while (RCC_GetSYSCLKSource() != 0x08)
        ; // 等待PLL作为系统时钟

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
