#include "GPIO.h"

/**
 * @brief 打开测试LED
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 依靠外部中断测量距离
 */
void GPIO_TestLED_ON(void)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_SET);
}

/**
 * @brief 关闭测试LED
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 依靠外部中断测量距离
 */
void GPIO_TestLED_OFF(void)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_RESET);
}

/**
 * @brief 测试LED初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 例程附带的测试程序
 * @note PB8-LED
 */
void GPIO_TestLED_Init(void)
{
    // 开启时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // 结构体定义
    GPIO_InitTypeDef GPIO_InitStructure;

    // PB8
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_TestLED_OFF();
}

/**
 * @brief WS2812引脚控制
 *
 * @param Signal 1或0电平信号
 *
 * @retval 无
 *
 * @note 无
 */
void GPIO_WS2812_PinConfig(uint8_t Signal)
{
    switch (Signal)
    {
    case 1:
        GPIO_SetBits(GPIOA, GPIO_Pin_12);
        break;
    case 0:
        GPIO_ResetBits(GPIOA, GPIO_Pin_12);
        break;
    }
}

/**
 * @brief WS2812引脚初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void GPIO_WS2812_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_INITSTRUCTURE;

    GPIO_INITSTRUCTURE.GPIO_Pin = GPIO_Pin_12;
    GPIO_INITSTRUCTURE.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_INITSTRUCTURE.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_INITSTRUCTURE);
}

/**
 * @brief 风扇引脚初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void GPIO_FAN_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_INITSTRUCTURE;

    GPIO_INITSTRUCTURE.GPIO_Pin = GPIO_Pin_8;
    GPIO_INITSTRUCTURE.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_INITSTRUCTURE.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_INITSTRUCTURE);
}

/**
 * @brief 按键初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note KEY1-PB1
 * @note KEY2-PB0
 * @note KEY3-PA0
 */
void GPIO_KEY_Init(void)
{
    // 开启时钟和结构体定义
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef GPIO_INITSTRUCTURE;

    // 引脚初始化：KEY1
    GPIO_INITSTRUCTURE.GPIO_Pin = GPIO_Pin_1;
    GPIO_INITSTRUCTURE.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_INITSTRUCTURE.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_INITSTRUCTURE);

    // 引脚初始化：KEY2
    GPIO_INITSTRUCTURE.GPIO_Pin = GPIO_Pin_0;
    GPIO_INITSTRUCTURE.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_INITSTRUCTURE.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_INITSTRUCTURE);

    // 引脚初始化：KEY3
    GPIO_INITSTRUCTURE.GPIO_Pin = GPIO_Pin_0;
    GPIO_INITSTRUCTURE.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_INITSTRUCTURE.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_INITSTRUCTURE);
}

/**
 * @brief 获取KEY1引脚电平
 *
 * @param 无
 *
 * @retval 返回1或0
 *
 * @note KEY1-PB1
 */
uint8_t GPIO_RetState_KEY1(void)
{
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1);
}

/**
 * @brief 获取KEY2引脚电平
 *
 * @param 无
 *
 * @retval 返回1或0
 *
 * @note KEY2-PB0
 */
uint8_t GPIO_RetState_KEY2(void)
{
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0);
}

/**
 * @brief 获取KEY3引脚电平
 *
 * @param 无
 *
 * @retval 返回1或0
 *
 * @note KEY3-PA0
 */
uint8_t GPIO_RetState_KEY3(void)
{
    return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
}

/**
 * @brief IO引脚初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void GPIO_InitPro(void)
{
    // GPIO_TestLED_Init();
    GPIO_WS2812_Init();
    GPIO_FAN_Init();
    GPIO_KEY_Init();
}
