#include "KEY.h"

// 按键状态(0：按键松开，1：按键短按，2：按键长按)
uint8_t KEY1_State = 0; // 按键1状态记录
uint8_t KEY2_State = 0; // 按键2状态记录
uint8_t KEY3_State = 0; // 按键3状态记录
uint8_t KEY_Count = 0;  // 按键计数(按下就计数)

// 经测试，在STM32F103C8T6上，KEY_CNT_longDown的自增并不是任务调度的1ms/次。大约20倍误差：计数10次时，实际时间流过200ms左右
// 通过串口输出时间比对、Keil5的Debug查看变量数值发现的规律
// 我也不清楚具体原因，只能先缩短KEY_CNT_longDown的长按判定时间

/**
 * @brief 按键状态设置
 *
 * @param Keyx 按键编号(KEY_NUMBER_xxx)
 * @param State 按键状态(KEY_STATE_xxx)
 *
 * @retval 无
 *
 * @note UPNONE按键松开，DOWNSHORT按键短按，DOWNLONG按键长按
 */
void KEY_SetState(uint8_t Keyx, uint8_t State)
{
    switch (Keyx)
    {
    case KEY_NUMBER_1:
    {
        KEY1_State = State;
    }
    break;

    case KEY_NUMBER_2:
    {
        KEY2_State = State;
    }
    break;

    case KEY_NUMBER_3:
    {
        KEY3_State = State;
    }
    break;
    }
}

/**
 * @brief 按键状态清除
 *
 * @param Keyx 按键编号(KEY_NUMBER_xxx)
 *
 * @retval 无
 *
 * @note 无
 */
void KEY_ClearState(uint8_t Keyx)
{
    switch (Keyx)
    {
    case KEY_NUMBER_1:
    {
        KEY_SetState(KEY_NUMBER_1, KEY_STATE_UPNONE);
    }
    break;

    case KEY_NUMBER_2:
    {
        KEY_SetState(KEY_NUMBER_2, KEY_STATE_UPNONE);
    }
    break;

    case KEY_NUMBER_3:
    {
        KEY_SetState(KEY_NUMBER_3, KEY_STATE_UPNONE);
    }
    break;
    }
}

/**
 * @brief 按键状态获取
 *
 * @param Keyx 按键编号(KEY_NUMBER_xxx)
 *
 * @retval 按键状态(KEY_STATE_xxx)
 *
 * @note UPNONE按键松开，DOWNSHORT按键短按，DOWNLONG按键长按
 */
uint8_t KEY_RetState(uint8_t Keyx)
{
    switch (Keyx)
    {
    case KEY_NUMBER_1:
    {
        return KEY1_State;
    }

    case KEY_NUMBER_2:
    {
        return KEY2_State;
    }

    case KEY_NUMBER_3:
    {
        return KEY3_State;
    }
    }

    return 255;
}

/**
 * @brief KEY1按键扫描
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 此函数独立分配1个任务
 * @note PCB设计时已经有电容滤波，不用软件消抖
 * @note 可以检测短按或长按事件，变量是KEY1_State
 */
void KEY1_Scanf(void)
{
    uint16_t KEY_CNT_longDown = 0;

    if (GPIO_RetState_KEY1() == 0)
    {
        vTaskDelay(5);
        if (GPIO_RetState_KEY1() == 0)
        {
            KEY_Count++;
            while (GPIO_RetState_KEY1() == 0)
            {
                KEY_CNT_longDown++;
                vTaskDelay(1);

                // 限幅
                if (KEY_CNT_longDown >= 60000)
                {
                    KEY_CNT_longDown = 60000;
                }
            }

            if (KEY_CNT_longDown >= 50)
            {
                KEY_SetState(KEY_NUMBER_1, KEY_STATE_DOWNLONG); // 长按
            }
            else
            {
                KEY_SetState(KEY_NUMBER_1, KEY_STATE_DOWNSHORT); // 短按
            }
        }
    }
}

/**
 * @brief KEY2按键扫描
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 此函数独立分配1个任务
 * @note PCB设计时已经有电容滤波，不用软件消抖
 * @note 可以检测短按或长按事件，变量是KEY2_State
 */
void KEY2_Scanf(void)
{
    uint16_t KEY_CNT_longDown = 0;

    if (GPIO_RetState_KEY2() == 0)
    {
        vTaskDelay(5);
        if (GPIO_RetState_KEY2() == 0)
        {
            KEY_Count++;
            while (GPIO_RetState_KEY2() == 0)
            {
                KEY_CNT_longDown++;
                vTaskDelay(1);

                // 限幅
                if (KEY_CNT_longDown >= 60000)
                {
                    KEY_CNT_longDown = 60000;
                }
            }

            if (KEY_CNT_longDown >= 50)
            {
                KEY_SetState(KEY_NUMBER_2, KEY_STATE_DOWNLONG); // 长按
            }
            else
            {
                KEY_SetState(KEY_NUMBER_2, KEY_STATE_DOWNSHORT); // 短按
            }
        }
    }
}

/**
 * @brief KEY3按键扫描
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 此函数独立分配1个任务
 * @note PCB设计时已经有电容滤波，不用软件消抖
 * @note 可以检测短按或长按事件，变量是KEY3_State
 */
void KEY3_Scanf(void)
{
    uint16_t KEY_CNT_longDown = 0;

    if (GPIO_RetState_KEY3() == 0)
    {
        vTaskDelay(5);
        if (GPIO_RetState_KEY3() == 0)
        {
            KEY_Count++;
            while (GPIO_RetState_KEY3() == 0)
            {
                KEY_CNT_longDown++;
                vTaskDelay(1);

                // 限幅
                if (KEY_CNT_longDown >= 60000)
                {
                    KEY_CNT_longDown = 60000;
                }
            }

            if (KEY_CNT_longDown >= 50)
            {
                KEY_SetState(KEY_NUMBER_3, KEY_STATE_DOWNLONG); // 长按
            }
            else
            {
                KEY_SetState(KEY_NUMBER_3, KEY_STATE_DOWNSHORT); // 短按
            }
        }
    }
}

/**
 * @brief 关闭按键事件监测
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 挂起所有按键事件监测的任务
 */
void KEY_KEYScanf_Disable(void)
{
    vTaskSuspend(KEY1_TASK);
    vTaskSuspend(KEY2_TASK);
    vTaskSuspend(KEY3_TASK);
}

/**
 * @brief 打开按键事件监测
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 恢复所有按键事件监测的任务
 */
void KEY_KEYScanf_Enable(void)
{
    vTaskResume(KEY1_TASK);
    vTaskResume(KEY2_TASK);
    vTaskResume(KEY3_TASK);
}

/**
 * @brief 按键初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 无
 */
void KEY_InitPro(void)
{
}
