#include "Flash.h"

uint16_t Flash_InitFlag = 0xAABB; // 闪存初始化标志位(0xAABB：已初始化)
uint16_t Flash_Buffer[FLASH_LENGTH_16BIT];

/**
 * @brief flash读1个半字
 *
 * @param Addr 地址
 *
 * @retval 无
 *
 * @note 无
 */
uint16_t Flash_ReadHalfWord(uint32_t Addr)
{
    return *((__IO uint16_t *)(Addr));
}

/**
 * @brief flash写数据
 *
 * @param Addr 地址
 * @param Data 1个半字
 *
 * @retval 无
 *
 * @note 无
 */
void Flash_WriteHalfWord(uint32_t Addr, uint16_t Data)
{
    FLASH_Unlock();
    FLASH_ProgramHalfWord(Addr, Data);
    FLASH_Lock();
}

/**
 * @brief flash页擦除
 *
 * @param PageAddr 页地址
 *
 * @retval 无
 *
 * @note 新开一页时，最后调用一下此函数
 * @note 可以由1写0，覆写数据时不能由0写1;如果需要由0写1，只能整页擦除
 */
void Flash_ErasePage(uint32_t PageAddr)
{
    FLASH_Unlock();
    FLASH_ErasePage(PageAddr);
    FLASH_Lock();
}

/**
 * @brief flash写数组
 *
 * @param Addr 地址
 * @param Data 数据
 * @param Length 数组长度
 *
 * @retval 无
 *
 * @note 无
 */
void Flash_WriteBuffer(uint32_t Addr, uint16_t *Data, uint16_t Length)
{
    for (uint16_t i = 0; i < Length; i++)
    {
        Flash_WriteHalfWord(Addr + i * 2, Data[i]);
    }
}

/**
 * @brief flash读取数组
 *
 * @param Addr 地址
 * @param Buffer 数组
 * @param Length 数组长度
 *
 * @retval 无
 *
 * @note 无
 */
void Flash_ReadBuffer(uint32_t Addr, uint16_t *Buffer, uint16_t Length)
{
    for (uint16_t i = 0; i < Length; i++)
    {
        Buffer[i] = Flash_ReadHalfWord(Addr + i * 2);
    }
}

/**
 * @brief 恢复数据到全局变量
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Flash_RecoverData(void)
{
    Flash_ReadBuffer(FLASH_ADDR_ENDPAGE, Flash_Buffer, FLASH_LENGTH_16BIT); // 读取数据到Flash数组

    // 从缓冲区读取
    Flash_InitFlag = Flash_Buffer[0];
    Value_OLED_NowBrightness = Flash_Buffer[1];
    State_OLEDMode = Flash_Buffer[2];
    State_OLEDDirection_LR = Flash_Buffer[3];
    State_OLEDDirection_TB = Flash_Buffer[4];
    Value_Fan_NowSpeed = Flash_Buffer[5];
    State_Fan = Flash_Buffer[6];
    Value_Light_Red_NowColor = Flash_Buffer[7];
    Value_Light_Green_NowColor = Flash_Buffer[8];
    Value_Light_Blue_NowColor = Flash_Buffer[9];
    State_Light = Flash_Buffer[10];
    State_Light_Auto = Flash_Buffer[11];
}

/**
 * @brief 保存数据到Flash
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void Flash_SavaData(void)
{
    Flash_ErasePage(FLASH_ADDR_ENDPAGE); // 擦除最后一页

    // 保存到缓冲区
    Flash_Buffer[0] = Flash_InitFlag;
    Flash_Buffer[1] = Value_OLED_NowBrightness;
    Flash_Buffer[2] = State_OLEDMode;
    Flash_Buffer[3] = State_OLEDDirection_LR;
    Flash_Buffer[4] = State_OLEDDirection_TB;
    Flash_Buffer[5] = Value_Fan_NowSpeed;
    Flash_Buffer[6] = State_Fan;
    Flash_Buffer[7] = Value_Light_Red_NowColor;
    Flash_Buffer[8] = Value_Light_Green_NowColor;
    Flash_Buffer[9] = Value_Light_Blue_NowColor;
    Flash_Buffer[10] = State_Light;
    Flash_Buffer[11] = State_Light_Auto;

    // 保存数据到Flash
    Flash_WriteBuffer(FLASH_ADDR_ENDPAGE, Flash_Buffer, FLASH_LENGTH_16BIT);
}

/**
 * @brief flash初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void FLash_InitPro(void)
{
    Flash_ReadBuffer(FLASH_ADDR_ENDPAGE, Flash_Buffer, FLASH_LENGTH_16BIT); // 只读出数据,不覆盖
    if (Flash_Buffer[0] != 0xAABB)
    {
        // 若数据不为0xAABB,说明此闪存页还未使用过,需要先载入1次数据
        Flash_SavaData();
    }

    Flash_RecoverData(); // 恢复数据
}
