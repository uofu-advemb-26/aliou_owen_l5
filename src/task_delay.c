#include <stdio.h>
#include <pico/stdlib.h>
#include <FreeRTOS.h>
#include <task.h>

#include "lab5_include.h"

void second_task(__unused void * params)
{
    while(1);
}

void main_task(__unused void *params)
{
    TaskHandle_t second_task_h;
    xTaskCreate(second_task, "SecondThread",
                configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &second_task_h);
    TaskHandle_t third_task_h;
    xTaskCreate(second_task, "SecondThread",
                configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &third_task_h);

    int toggle = 0;
    while (1) {
        toggle = !toggle;
        gpio_put(OUT_PIN, toggle);
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
    }
}



int main(void)
{
    stdio_init_all();
    gpio_init(OUT_PIN);
    gpio_set_dir(OUT_PIN, GPIO_OUT);
    const char *rtos_name = "FreeRTOS";

    TaskHandle_t task;
    xTaskCreate(main_task, "MainThread",
                configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &task);
    vTaskStartScheduler();
    return 0;
}