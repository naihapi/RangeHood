#include "Delay.h"

uint8_t Delay_Finish = 0;

/**
 * @brief 定时器2微秒级延时
 *
 * @param xus 微秒数值
 *
 * @retval 无
 *
 * @note 无
 */
void Delay_us(uint32_t xus)
{
    while (Delay_Finish)
    {
    }

    TIM_SetAutoreload(TIM2, xus);
    TIM_Cmd(TIM2, ENABLE);

    while (!Delay_Finish)
    {
    }

    Delay_Finish = 0;
}

/**
 * @brief 定时器2毫秒级延时
 *
 * @param 毫秒数值
 *
 * @retval 无
 *
 * @note 使用TIM2计数延时
 */
void Delay_ms(uint32_t xms)
{
    while (xms--)
    {
        Delay_us(1000);
    }
}

/**
 * @brief 定时器2秒级延时
 *
 * @param 秒数值
 *
 * @retval 无
 *
 * @note 使用TIM2计数延时
 */
void Delay_s(uint32_t xs)
{
    while (xs--)
    {
        Delay_ms(1000);
    }
}

/**
 * @brief 定时器2中断服务函数
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 1ms中断1次
 */
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        TIM_Cmd(TIM2, DISABLE);
        Delay_Finish = 1;
    }

    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}
