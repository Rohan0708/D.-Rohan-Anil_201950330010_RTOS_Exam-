
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/timers.h>



TimerHandle_t motor_handle;

void Tasklog_1(void *pvParameter)
{
    while(1)
    {
        printf(" TASK LOG 1 RUNNING\n");
        
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
    //vTaskDelete(NULL);
}

void Tasklog_2(void *pvParameter)
{
    while(1)
    {
        printf(" TASK LOG 2 RUNNING\n");
        
        vTaskDelay(2000/ portTICK_PERIOD_MS);
    }
    //vTaskDelete(NULL);
}

void Tasklog_3(void *pvParameter)
{
    int sensor_data = 0;
    while(1)
    {
        sensor_data++;
        printf(" TASK LOG 3 RUNNING\n");
        
        vTaskDelay(5000/ portTICK_PERIOD_MS);
        if(sensor_data == 2)
        {
            xTimerStart(motor_handle,0);
        }
    }
    //vTaskDelete(NULL);
}

void motoroff(TimerHandle_t xtimer)
{
    printf(" Timer handler");
}


void app_main(void)
{
   
    BaseType_t result;
    TimerHandle_t xHandleTaskLog_1, xHandleTaskLog_2, xHandleTaskLog_3;
    
    result = xTaskCreate(Tasklog_1, "TaskLog_1", 2048, NULL, 5, &xHandleTaskLog_1);
    if (result == pdPASS)
    {
        printf("TASK LOG_1 CREATED\n");
    }

    result = xTaskCreate(Tasklog_2, "TaskLog_2", 2048, NULL, 6, &xHandleTaskLog_2);
    if (result == pdPASS)
    {
        printf("TASK LOG_2 CREATED\n");
    }
    
    result = xTaskCreate(Tasklog_3, "TaskLog_3", 2048, NULL, 7, &xHandleTaskLog_3);
    if (result == pdPASS)
    {
        printf("TASK LOG_3 CREATED\n");
    }
    motor_handle = xTaskCreate("motoroff",pdMS_TO_TICKS(2000),false,NULL,motoroff);
    
}
