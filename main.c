//
// Created by Yuri Moiseyenko on 2024-07-31.
//
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "FreeRTOS.h"
#include "task.h"
#define ON_BOARD_TASK_PRIORITY				( tskIDLE_PRIORITY + 1UL )

uint LED_PIN = 13;
uint RED_PIN = 17;
uint YELLOW_PIN = 15;
uint BLUE_PIN = 8;

void vTask(uint pin, TickType_t delay);

void initPins();

void vGreenBlinkTask() {
    vTask(LED_PIN, 250);
}

void vRedBlinkTask() {
    vTask(RED_PIN, 150);
}

void vYellowBlinkTask() {
    vTask(YELLOW_PIN, 320);
}

void vBlueBlinkTask() {
    vTask(BLUE_PIN, 500);
}

void vTask(uint pin, TickType_t delay) {
    for (;;) {
        gpio_put(pin, 1);
        vTaskDelay(delay);
        gpio_put(pin, 0);
        vTaskDelay(delay);
    }
}

void vOnBoardTask() {
    for(;;) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        cyw43_delay_ms(15);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        printf("heartbeat\n");
        cyw43_delay_ms(5000);
    }
}


int main() {

    //initPins pico sdk
    stdio_init_all();
    //initPins pico wifi
    if (cyw43_arch_init()) {
        printf("Wi-Fi initPins failed");
        return -1;
    }
    initPins();
    TaskHandle_t onBoardTask;
    xTaskCreate(vOnBoardTask, "On Board LED", configMINIMAL_STACK_SIZE, NULL, ON_BOARD_TASK_PRIORITY, &onBoardTask);
#if NO_SYS && configUSE_CORE_AFFINITY && configNUM_CORES > 1
    // we must bind the main task to one core (well at least while the init is called)
    // (note we only do this in NO_SYS mode, because cyw43_arch_freertos
    // takes care of it otherwise)
    vTaskCoreAffinitySet(task, 1);
#endif

    xTaskCreate(vGreenBlinkTask, "Green Blink Task", 128, NULL, 1, NULL);
    xTaskCreate(vYellowBlinkTask, "Blue Led Task", 128, NULL, 1, NULL);
    xTaskCreate(vRedBlinkTask, "Red Blink Task", 128, NULL, 1, NULL);
    xTaskCreate(vBlueBlinkTask, "Blue Blink Taks", 128, NULL, 1, NULL);
    vTaskStartScheduler();
}

void initPins() {
    printf("initializing pins...\n");
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_init(RED_PIN);
    gpio_set_dir(RED_PIN, GPIO_OUT);
    gpio_init(YELLOW_PIN);
    gpio_set_dir(YELLOW_PIN, GPIO_OUT);
    gpio_init(BLUE_PIN);
    gpio_set_dir(BLUE_PIN, GPIO_OUT);
}
