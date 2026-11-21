#ifdef APP_DEVICE

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "modules/macro.h"
#include "modules/wifi.h"
#include "packets/uplink.h"

static const char *TAG = "DEVICE";

void app_init    (void);
void app_transmit(void);

void app_main(void) {
    vTaskDelay(pdMS_TO_TICKS(1000));
    app_init();
    app_transmit();
}

void app_init(void) {
    if (!wifi_init(1)) LOG_RETURN(TAG, "Failed to initialize Wi-Fi");
    else               ESP_LOGI  (TAG, "Wi-Fi initialized");
}

void app_transmit(void) {
    // new uplink packet
    bc_uplink_t *uplink = uplink_new();
    if (!uplink) LOG_RETURN(TAG, "Failed to allocate uplink packet");
    uplink_init(uplink);
    // cleanup
    uplink_free(uplink);
}

#endif