#ifndef _TIM_H
#define _TIM_H

// MCU型号
#include "stm32f10x.h"

// API
void TIM_FAN_SetDuty(uint8_t Dutyx);
void TIM_InitPro(void);

#endif
