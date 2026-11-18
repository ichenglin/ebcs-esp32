#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "wifi.h"

bool wifi_init(void) {
    if (nvs_flash_init()                != ESP_OK) return false;
    if (esp_netif_init()                != ESP_OK) return false;
    if (esp_event_loop_create_default() != ESP_OK) return false;
    wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
    if (esp_wifi_init(&config)           != ESP_OK) return false;
    if (esp_wifi_set_mode(WIFI_MODE_STA) != ESP_OK) return false;
    if (esp_wifi_start()                 != ESP_OK) return false;
    return true;
}

bool wifi_promiscuous(void) {
    if (esp_wifi_set_promiscuous_rx_cb(wifi_promiscuous_callback) != ESP_OK) return false;
    if (esp_wifi_set_promiscuous(true)                            != ESP_OK) return false;
    return true;
}

void wifi_promiscuous_callback(void *buf, wifi_promiscuous_pkt_type_t type) {
    ESP_LOGI("TEST", "received packet of type %d", type);
}