#include "MyTASK.h"

TimerHandle_t TIMER1_Handler;
TimerHandle_t TIMER2_Handler;
TaskHandle_t TASK1_Handler;
TaskHandle_t TASK2_Handler;
TaskHandle_t TASK3_Handler;
TaskHandle_t TASK4_Handler;
TaskHandle_t TASK5_Handler;
TaskHandle_t TASK6_Handler;
TaskHandle_t TASK7_Handler;
TaskHandle_t TASK8_Handler;
TaskHandle_t TASK9_Handler;
TaskHandle_t TASK10_Handler;
TaskHandle_t TASK11_Handler;
TaskHandle_t TASK12_Handler;
TaskHandle_t TASK13_Handler;
TaskHandle_t TASK14_Handler;
TaskHandle_t TASK15_Handler;
TaskHandle_t TASK_START_Handler;

uint32_t ms = 0;
void TIMER1(TimerHandle_t xTimer)
{
    // 获取当前嘀嗒计数
    TickType_t xTickCount = xTaskGetTickCount();

    // 转换为毫秒
    ms = xTickCount * portTICK_PERIOD_MS;
}

void TIMER2(TimerHandle_t xTimer)
{
    TickType_t xTickCount = xTaskGetTickCount();
}

/**
 * @brief 任务1
 *
 * @note KEY1检测
 */
void TASK1(void *pvParameters)
{

    while (1)
    {
        KEY1_Scanf();
    }
}

/**
 * @brief 任务2
 *
 * @note 无
 */
void TASK2(void *pvParameters)
{
    while (1)
    {
        KEY2_Scanf();
    }
}

/**
 * @brief 任务3
 *
 * @note 无
 */
void TASK3(void *pvParameters)
{
    while (1)
    {
        KEY3_Scanf();
    }
}

/**
 * @brief 任务4
 *
 * @note 无
 */
void TASK4(void *pvParameters)
{
    OLED_Init();
    while (1)
    {
        Build_ControlPro();
        OLED_Update();
    }
}

/**
 * @brief 任务5
 *
 * @note 无
 */
void TASK5(void *pvParameters)
{
    MySystem_Fanlight_Function_Init();
    while (1)
    {
        MySystem_Fanlight_Function();

        vTaskDelay(500);
    }
}

/**
 * @brief 任务6
 *
 * @note 无
 */
void TASK6(void *pvParameters)
{
    while (1)
    {
        Flash_SavaData();
        MySystem_GetFreeHeap();

        vTaskDelay(1000);
    }
}

/**
 * @brief 任务7
 *
 * @note 无
 */
void TASK7(void *pvParameters)
{
    while (1)
    {
        MySystem_FanSpeed_Function();
        vTaskDelay(100);
    }
}

/**
 * @brief 任务8
 *
 * @note 无
 */
void TASK8(void *pvParameters)
{
    while (1)
    {
    }
}

/**
 * @brief 任务9
 *
 * @note 无
 */
void TASK9(void *pvParameters)
{
    while (1)
    {
    }
}

/**
 * @brief 任务10
 *
 * @note 无
 */
void TASK10(void *pvParameters)
{
    while (1)
    {
    }
}

/**
 * @brief 任务11
 *
 * @note 无
 */
void TASK11(void *pvParameters)
{
    while (1)
    {
    }
}

/**
 * @brief 任务12
 *
 * @note 无
 */
void TASK12(void *pvParameters)
{
    while (1)
    {
    }
}

/**
 * @brief 任务13
 *
 * @note 无
 */
void TASK13(void *pvParameters)
{
    while (1)
    {
    }
}

/**
 * @brief 任务14
 *
 * @note 无
 */
void TASK14(void *pvParameters)
{
    while (1)
    {
    }
}

/**
 * @brief 任务15
 *
 * @note 无
 */
void TASK15(void *pvParameters)
{
    while (1)
    {
    }
}

void Timer_Init(void)
{
    TIMER1_Handler = xTimerCreate((char *)"TIMER1", pdMS_TO_TICKS(5 * 1000), pdTRUE, (void *)0, TIMER1);
    TIMER2_Handler = xTimerCreate("TIMER2", pdMS_TO_TICKS(10 * 1000), pdTRUE, (void *)1, TIMER2);

    xTimerStart(TIMER1_Handler, 0);
    xTimerStart(TIMER2_Handler, 0);
}

/**
 * @brief 打开任务
 *
 * @param pvParameters 系统传递数据
 *
 * @retval 无
 *
 * @note 打开其它的所有任务
 */
void Task_Start(void *pvParameters)
{
    taskENTER_CRITICAL(); // 进入临界区(中断关闭)
    Timer_Init();

    xTaskCreate((TaskFunction_t)TASK1,
                (char *)"TASK1",
                (configSTACK_DEPTH_TYPE)TASK1_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK1_PRIORITY,
                (TaskHandle_t *)&TASK1_Handler);

    xTaskCreate((TaskFunction_t)TASK2,
                (char *)"TASK2",
                (configSTACK_DEPTH_TYPE)TASK2_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK2_PRIORITY,
                (TaskHandle_t *)&TASK2_Handler);

    xTaskCreate((TaskFunction_t)TASK3,
                (char *)"TASK3",
                (configSTACK_DEPTH_TYPE)TASK3_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK3_PRIORITY,
                (TaskHandle_t *)&TASK3_Handler);

    xTaskCreate((TaskFunction_t)TASK4,
                (char *)"TASK4",
                (configSTACK_DEPTH_TYPE)TASK4_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK4_PRIORITY,
                (TaskHandle_t *)&TASK4_Handler);

    xTaskCreate((TaskFunction_t)TASK5,
                (char *)"TASK5",
                (configSTACK_DEPTH_TYPE)TASK5_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK5_PRIORITY,
                (TaskHandle_t *)&TASK5_Handler);

    xTaskCreate((TaskFunction_t)TASK6,
                (char *)"TASK6",
                (configSTACK_DEPTH_TYPE)TASK6_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK6_PRIORITY,
                (TaskHandle_t *)&TASK6_Handler);

    xTaskCreate((TaskFunction_t)TASK7,
                (char *)"TASK7",
                (configSTACK_DEPTH_TYPE)TASK7_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK7_PRIORITY,
                (TaskHandle_t *)&TASK7_Handler);

    xTaskCreate((TaskFunction_t)TASK8,
                (char *)"TASK8",
                (configSTACK_DEPTH_TYPE)TASK8_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK8_PRIORITY,
                (TaskHandle_t *)&TASK8_Handler);

    xTaskCreate((TaskFunction_t)TASK9,
                (char *)"TASK9",
                (configSTACK_DEPTH_TYPE)TASK9_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK9_PRIORITY,
                (TaskHandle_t *)&TASK9_Handler);

    xTaskCreate((TaskFunction_t)TASK10,
                (char *)"TASK10",
                (configSTACK_DEPTH_TYPE)TASK10_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK10_PRIORITY,
                (TaskHandle_t *)&TASK10_Handler);

    xTaskCreate((TaskFunction_t)TASK11,
                (char *)"TASK11",
                (configSTACK_DEPTH_TYPE)TASK11_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK11_PRIORITY,
                (TaskHandle_t *)&TASK11_Handler);

    xTaskCreate((TaskFunction_t)TASK12,
                (char *)"TASK12",
                (configSTACK_DEPTH_TYPE)TASK12_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK12_PRIORITY,
                (TaskHandle_t *)&TASK12_Handler);

    xTaskCreate((TaskFunction_t)TASK13,
                (char *)"TASK13",
                (configSTACK_DEPTH_TYPE)TASK13_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK13_PRIORITY,
                (TaskHandle_t *)&TASK13_Handler);

    xTaskCreate((TaskFunction_t)TASK14,
                (char *)"TASK14",
                (configSTACK_DEPTH_TYPE)TASK14_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK14_PRIORITY,
                (TaskHandle_t *)&TASK14_Handler);

    xTaskCreate((TaskFunction_t)TASK15,
                (char *)"TASK15",
                (configSTACK_DEPTH_TYPE)TASK15_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK15_PRIORITY,
                (TaskHandle_t *)&TASK15_Handler);

    vTaskDelete(NULL);   // 删除任务
    taskEXIT_CRITICAL(); // 退出临界区(中断打开)
}

/**
 * @brief 任务初始化
 *
 * @param 无
 *
 * @retval 无
 *
 * @note 调用后，将开始RTOS任务调度
 */
void TASK_InitPro(void)
{
    /*中断优先级分组(全抢占优先级模式)*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    xTaskCreate((TaskFunction_t)Task_Start,                    // 函数名称
                (char *)"Task_Start",                          // 任务名称
                (configSTACK_DEPTH_TYPE)TASK_START_STACK_SIZE, // 栈空间
                (void *)NULL,                                  // 传给任务的参数
                (UBaseType_t)TASK_START_PRIORITY,              // 优先级
                (TaskHandle_t *)&TASK_START_Handler);          // 任务句柄

    vTaskStartScheduler(); // 启动任务调度器
}
