
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

QueueHandle_t sensor_queue;

TaskHandle_t xHandleTaskLog_1;
TaskHandle_t xHandleTaskLog_2,xHandleTaskLog_3, xHandleTaskLog_4, xHandleTaskLog_5 ;

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
    while(1)
    {
        printf(" TASK LOG 3 RUNNING\n");
        
        vTaskDelay(5000/ portTICK_PERIOD_MS);
    }
    //vTaskDelete(NULL);
}

void Tasklog_4(void *pvParameter)
{
    int sensor_data = 0;
    while(1)
    {
        
        printf(" TASK LOG 4 RUNNING\n");
        sensor_data++;
        printf("sensor task: %d\n\n",sensor_data);
        xQueueSend(sensor_queue,&sensor_data, portMAX_DELAY);
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
    //vTaskDelete(NULL);
}

void Tasklog_5(void *pvParameter)
{
   while(1)
   {
        int recv_data;
        printf(" TASK LOG 5 RUNNING\n");
        xQueueReceive(sensor_queue,&recv_data, portMAX_DELAY);
        printf("Rec_data: %d\n\n",recv_data);
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
    //vTaskDelete(NULL);
}

void app_main(void)
{
    sensor_queue = xQueueCreate(10, sizeof(int));
    BaseType_t result1, result2, result3, result4, result5;

    
    result1 = xTaskCreate(Tasklog_1, "TaskLog_1", 2048, NULL, 5, &xHandleTaskLog_1);
    if (result1 == pdPASS)
    {
        printf("TASK LOG_1 CREATED\n");
    }

    result2 = xTaskCreate(Tasklog_2, "TaskLog_2", 2048, NULL, 6, &xHandleTaskLog_2);
    if (result2 == pdPASS)
    {
        printf("TASK LOG_2 CREATED\n");
    }
    
    result3 = xTaskCreate(Tasklog_3, "TaskLog_3", 2048, NULL, 7, &xHandleTaskLog_3);
    if (result3 == pdPASS)
    {
        printf("TASK LOG_3 CREATED\n");
    }
    
    result4 = xTaskCreate(Tasklog_4, "Tasklog_4", 2048, NULL, 8, &xHandleTaskLog_4);
    if (result4 == pdPASS)
    {
        printf("TASK LOG_4 CREATED\n");
    }
    
    result5 = xTaskCreate(Tasklog_5, "TaskLog_5", 2048, NULL, 9, &xHandleTaskLog_5);
    if (result5 == pdPASS)
    {
        printf("TASK LOG_5 CREATED\n");
    }
    
}
