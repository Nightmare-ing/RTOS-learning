#include "FreeRTOS.h"
#include "board/board.h"
#include "board/led.h"
#include "led/led.h"
#include "task.h"
#include <stdbool.h>

static void led0_task(void *pvParameters) {
    struct led *led0 = (struct led *)pvParameters;
    while (true) {
        led_toggle(led0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

static void led1_task(void *pvParameters) {
    struct led *led1 = (struct led *)pvParameters;
    while (true) {
        led_toggle(led1);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void) {
    if (board_init() != 0) {
        while (true) {
        }
    }

    static struct led led0;
    static struct led led1;
    if (board_led_bind(BOARD_LED_0, &led0) != 0 ||
        board_led_bind(BOARD_LED_1, &led1) != 0) {
        while (true) {
        }
    }

    if (xTaskCreate(led0_task, "led0 flash task", configMINIMAL_STACK_SIZE,
                    &led0, tskIDLE_PRIORITY + 1U, NULL) != pdPASS) {
        while (true) {
        }
    }

    if (xTaskCreate(led1_task, "led1 flash task", configMINIMAL_STACK_SIZE,
                    &led1, tskIDLE_PRIORITY + 1U, NULL) != pdPASS) {
        while (true) {
        }
    }

    vTaskStartScheduler();

    while (true) {
    }
}

void vApplicationStackOverflowHook(TaskHandle_t task, char *task_name) {
    (void)task;
    (void)task_name;
    while (true) {
    }
}
