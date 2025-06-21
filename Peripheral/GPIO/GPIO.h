#ifndef _GPIO_H
#define _GPIO_H

// MCU型号
#include "stm32f10x.h"

// 软件
#include "Delay.h"

// API
void GPIO_TestLED_ON(void);
void GPIO_TestLED_OFF(void);
void GPIO_WS2812_PinConfig(uint8_t Signal);
uint8_t GPIO_RetState_KEY1(void);
uint8_t GPIO_RetState_KEY2(void);
uint8_t GPIO_RetState_KEY3(void);
void GPIO_InitPro(void);

#endif
