#ifndef _Delay_H
#define _Delay_H

// MCU型号
#include "stm32f10x.h"

// 外设
#include "GPIO.h"

// 变量
//...

// API
void Delay_us(uint32_t xus);
void Delay_ms(uint32_t xms);
void Delay_s(uint32_t xs);

#endif
