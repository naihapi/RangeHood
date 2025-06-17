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

    /*---外件---*/
    //...

    /*---软件---*/
    //...

    /*开启任务调度*/
    TASK_InitPro();
}
