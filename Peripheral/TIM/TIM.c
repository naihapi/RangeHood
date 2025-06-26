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
    TIM_TimeBaseInitStructure.TIM_Period = 1 - 1;     // ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1; // PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = DISABLE;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_Init(&NVIC_InitStructure);

    TIM_SetCounter(TIM2, 0);
    TIM_Cmd(TIM2, DISABLE);
}

/**
 * @brief 定时器3初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 此函数用于WS2812输出
 * @note PWM+DMA,占空比0~90%
 * @note 请注意，此函数未配置完成
 */
void TIM_FAN_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1;     // ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;    // PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; // 高级定时器需要设置
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0; // 初始占空比
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);

    // 高级定时器需要启用预装载
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

    // TIM_SetCounter(TIM1, 0);
    TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE); // 高级定时器必须调用这个
    TIM_Cmd(TIM1, ENABLE);
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
    TIM_FAN_Init();
}
