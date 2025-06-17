#include "TIM.h"

/**
 * @brief 定时器2初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 此函数用于中断延时，详见Delay.c，TIM2的中断服务函数也在那里
 */
void TIM_Delay_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 999;                // ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 71;              // PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = DISABLE; // 溢出x次后才触发更新中断
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_Init(&NVIC_InitStructure);

    TIM_SetCounter(TIM2, 0);
    TIM_Cmd(TIM2, ENABLE);
}
/**
 * @brief 定时器初始化汇总
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void TIM_InitPro(void)
{
    TIM_Delay_Init();
}
