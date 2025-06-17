#include "WS2812.h"

/**
 * @brief WS2812发送1字节
 *
 * @param Byte 1个字节
 *
 * @retval 无
 *
 * @note 无
 */
void WS2812_SendByte(uint8_t Byte)
{
    uint8_t Bit = 0;

    for (uint8_t i = 0; i < 8; i++)
    {
        Bit = Byte & 0x80;

        if (Bit)
        {
            GPIO_WS2812_PinConfig(HIGH);
            Delay_us(1);

            // 经测试，函数封装导致时序变慢，所以直接切换电平
            GPIO_ResetBits(GPIOA, GPIO_Pin_12);
        }
        else
        {
            // 经测试，函数封装导致时序变慢，所以直接切换电平
            GPIO_SetBits(GPIOA, GPIO_Pin_12);

            GPIO_WS2812_PinConfig(LOW);
            Delay_us(1);
        }
        Byte <<= 1;
    }
}

/**
 * @brief WS2812发送1个灯珠颜色
 *
 * @param Red 8位红色数据
 * @param Green 8位绿色数据
 * @param Blue 8位蓝色数据
 *
 * @retval 无
 *
 * @note 无
 */
void WS2812_SendColor(uint8_t Red, uint8_t Green, uint8_t Blue)
{
    uint8_t RGB[3];
    RGB[0] = Green;
    RGB[1] = Red;
    RGB[2] = Blue;

    for (uint8_t i = 0; i < 3; i++)
    {
        WS2812_SendByte(RGB[i]);
    }
}

/**
 * @brief WS2812发送x个灯珠颜色
 *
 * @param Number
 * @param Red 8位红色数据
 * @param Green 8位绿色数据
 * @param Blue 8位蓝色数据
 *
 * @retval 无
 *
 * @note 无
 */
void WS2812_SendRGB(uint8_t Number, uint8_t Red, uint8_t Green, uint8_t Blue)
{
    for (uint8_t i = 0; i < Number; i++)
    {
        WS2812_SendColor(Red, Green, Blue);
    }
}

/**
 * @brief WS2812灯珠初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void WS2812_InitPro(void)
{
}