#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

#include "modules/gpio.h"

static void _gpio_task   (void *arg);
static void _gpio_handler(void *arg);

static QueueHandle_t   gpio_queue;
static gpio_callback_t gpio_callback;

void gpio_init(gpio_num_t pin) {
    gpio_config_t config = {
        .pin_bit_mask = (1ULL << pin),
        .mode         = GPIO_MODE_INPUT,
        .pull_up_en   = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_ANYEDGE
    };
    gpio_config(&config);
}

void gpio_event(gpio_num_t pin) {
    gpio_queue = xQueueCreate(10, sizeof(gpio_num_t));
    xTaskCreate(_gpio_task, "gpio_task", 2048, NULL, 10, NULL);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(pin, _gpio_handler, ((void*) pin));
}

void gpio_listener(gpio_callback_t callback) {
    gpio_callback = callback;
}

static void _gpio_task(void *arg) {
    gpio_num_t gpio_num;
    while (true) if (xQueueReceive(gpio_queue, &gpio_num, portMAX_DELAY)) {
        gpio_level_t level = (gpio_get_level(gpio_num) ? GPIO_EVENT_HIGH : GPIO_EVENT_LOW);
        if (gpio_callback != NULL) gpio_callback(gpio_num, level);
    }
}

static void IRAM_ATTR _gpio_handler(void *arg) {
    gpio_num_t gpio_num = ((gpio_num_t) arg);
    xQueueSendFromISR(gpio_queue, &gpio_num, NULL);
}
