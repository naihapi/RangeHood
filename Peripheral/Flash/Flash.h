#ifndef _Flash_H
#define _Flash_H

// MCU型号
#include "stm32f10x.h"

// 软件
#include "MyMenu.h"

// 宏定义
#define FLASH_ADDR_ENDPAGE 0x08007C00 // 最后1页的地址
#define FLASH_LENGTH_16BIT 512        // 1k位置分16bit

// 变量
//...

// API
void FLash_InitPro(void);
void Flash_SavaData(void);
void Flash_RecoverData(void);

#endif
