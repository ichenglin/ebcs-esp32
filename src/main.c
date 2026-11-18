#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"

#include "modules/wifi.h"

static const char *TAG = "MAIN";

void app_main(void) {
    vTaskDelay(pdMS_TO_TICKS(1000));
    if (!wifi_init())        { ESP_LOGE(TAG, "Failed to initialize Wi-Fi");             return; }
    if (!wifi_promiscuous()) { ESP_LOGE(TAG, "Failed to start Wi-Fi promiscuous mode"); return; }
    ESP_LOGI(TAG, "Wi-Fi promiscuous mode started successfully!");
}
