#ifndef __WS2812_H__
#define __WS2812_H__

// MCU型号
#include "stm32f10x.h"

// API
void WS2812_SendByte(uint8_t Byte);
void WS2812_SendColor(uint8_t Red, uint8_t Green, uint8_t Blue);
void WS2812_SendRGB(uint8_t Number, uint8_t Red, uint8_t Green, uint8_t Blue);

#endif