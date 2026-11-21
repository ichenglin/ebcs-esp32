#ifdef APP_DEVICE

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "modules/wifi.h"

static const char *TAG = "DEVICE";

void app_main(void) {
    vTaskDelay(pdMS_TO_TICKS(1000));
    // initialize
    if (!wifi_init(1)) { ESP_LOGE(TAG, "Failed to initialize Wi-Fi"); return; }
    ESP_LOGI(TAG, "Wi-Fi initialized");

}

#endif