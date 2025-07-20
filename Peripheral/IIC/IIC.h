#ifndef _IIC_H
#define _IIC_H

// MCU型号
#include "stm32f10x.h"

// 宏定义
#define IIC_OK 1        // 成功
#define IIC_TIMEOUT 0   // 超时
#define IIC_BUS_ERROR 2 // 总线错误
#define IIC_ARB_LOST 3  // 仲裁丢失
#define IIC_ACK_FAIL 4  // 应答失败
#define IIC_OVERRUN 5   // 数据溢出
#define IIC_PEC_ERROR 6 // PEC校验错误（仅某些模式）
#define IIC_MPU6050_ADDR 0xD0
#define IIC_OLED_ADDR 0x78

// API
void IIC_InitPro(void);
uint8_t IIC1_WaitEvent(I2C_TypeDef *I2Cx, uint32_t I2C_EVENT);
void IIC1_OLED_WriteCommand(uint8_t Command);
void IIC1_OLED_WriteData(uint8_t *Data, uint8_t Count);

#endif
