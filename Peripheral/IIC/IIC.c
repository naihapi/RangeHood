#include "IIC.h"

/**
 * @brief IIC初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void IIC_InitPro(void)
{
    // 配置IIC
    I2C_InitTypeDef I2C_InitStructure;                                        // IIC初始化结构体
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;                                // IIC默认模式
    I2C_InitStructure.I2C_ClockSpeed = 300000;                                // 速率40kHz
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;                        // 占空比2(仅大于100kHz生效)
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;                               // 使能应答
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; // 7位地址
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;                                 // 配置从设备地址
    I2C_Init(I2C1, &I2C_InitStructure);                                       // 初始化IIC1

    I2C_Cmd(I2C1, ENABLE);
}

/**
 * @brief 等待IIC事件
 *
 * @param I2Cx I2C通道选择
 * @param I2C_EVENT 事件选择
 *
 * @retval 0 等待超时
 *
 * @note 无
 */
uint8_t IIC1_WaitEvent(I2C_TypeDef *I2Cx, uint32_t I2C_EVENT)
{
    uint32_t Timeout = 20000;

    while (I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS)
    {
        // 检测所有硬件错误标志
        if (I2C_GetFlagStatus(I2Cx, I2C_FLAG_BERR))
        {
            I2C_ClearFlag(I2Cx, I2C_FLAG_BERR);
            return IIC_BUS_ERROR; // 总线错误（如SCL被意外拉低）
        }

        if (I2C_GetFlagStatus(I2Cx, I2C_FLAG_ARLO))
        {
            I2C_ClearFlag(I2Cx, I2C_FLAG_ARLO);
            return IIC_ARB_LOST; // 多主机竞争时仲裁丢失
        }

        if (I2C_GetFlagStatus(I2Cx, I2C_FLAG_AF))
        {
            I2C_ClearFlag(I2Cx, I2C_FLAG_AF);
            return IIC_ACK_FAIL; // 从机未返回ACK
        }

        if (I2C_GetFlagStatus(I2Cx, I2C_FLAG_OVR))
        {
            I2C_ClearFlag(I2Cx, I2C_FLAG_OVR);
            return IIC_OVERRUN; // 数据溢出（时钟过快）
        }

        if (Timeout-- == 0)
        {
            IIC_InitPro();
            return IIC_TIMEOUT; // 超时
        }
    }
    return IIC_OK; // 成功
}

/**
 * @brief IIC1写命令
 *
 * @param Command 指令
 *
 * @retval 无
 *
 * @note 此函数适用于OLED，以对接江科大的显示库
 */
void IIC1_OLED_WriteCommand(uint8_t Command)
{
    // I2C起始
    I2C_GenerateSTART(I2C1, ENABLE);
    if (!IIC1_WaitEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
    {
        return;
    }

    // 发送OLED的I2C从机地址
    I2C_Send7bitAddress(I2C1, IIC_OLED_ADDR, I2C_Direction_Transmitter);
    IIC1_WaitEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

    // 控制字节，给0x00，表示即将写命令
    I2C_SendData(I2C1, 0x00);
    IIC1_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED);

    // 写入指定的命令
    I2C_SendData(I2C1, Command);
    IIC1_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING);

    // I2C终止
    I2C_GenerateSTOP(I2C1, ENABLE);
}

/**
 * @brief OLED写命令
 *
 * @param Data 数据
 * @param Count 写次数
 *
 * @retval 无
 *
 * @note 此函数适用于OLED，以对接江科大的显示库
 */
void IIC1_OLED_WriteData(uint8_t *Data, uint8_t Count)
{
    uint8_t i;

    // I2C起始
    I2C_GenerateSTART(I2C1, ENABLE);
    IIC1_WaitEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT);

    // 发送OLED的I2C从机地址
    I2C_Send7bitAddress(I2C1, IIC_OLED_ADDR, I2C_Direction_Transmitter);
    IIC1_WaitEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

    // 控制字节，给0x40，表示即将写数据
    I2C_SendData(I2C1, 0x40);
    IIC1_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED);

    /*循环Count次，进行连续的数据写入*/
    for (i = 0; i < Count; i++)
    {
        // 依次发送Data的每一个数据
        I2C_SendData(I2C1, Data[i]);
        IIC1_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING);
    }

    // I2C终止
    I2C_GenerateSTOP(I2C1, ENABLE);
}
