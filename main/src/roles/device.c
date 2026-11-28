#include <time.h>

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "constants/action.h"
#include "constants/base.h"
#include "constants/mac.h"
#include "constants/uplink.h"
#include "modules/gpio.h"
#include "modules/macro.h"
#include "modules/wifi.h"
#include "packets/uplink.h"

#define DEVICE_GPIO_BUTTON ((gpio_num_t) CONFIG_DEVICE_GPIO_BUTTON)
#define DEVICE_CHANNEL     ((uint8_t)    CONFIG_BOARD_CHANNEL)

static const char *TAG = "DEVICE";

void app_init    (void);
void app_event   (gpio_num_t pin, gpio_level_t level);
void app_transmit(void);

void app_main(void) {
    app_init();
    gpio_init (DEVICE_GPIO_BUTTON);
    gpio_event(DEVICE_GPIO_BUTTON);
    gpio_listener(app_event);
}

void app_init(void) {
    if (!wifi_init(DEVICE_CHANNEL)) LOG_RETURN(TAG, "Failed to Initialize Wi-Fi");
    else                            ESP_LOGI  (TAG, "Wi-Fi Initialized");
}

void app_event(gpio_num_t pin, gpio_level_t level) {
    if (pin   != DEVICE_GPIO_BUTTON) return;
    if (level != GPIO_EVENT_LOW)     return;
    ESP_LOGI(TAG, "Transmitting Uplink Packet...");
    app_transmit();
}

void app_transmit(void) {
    // new uplink packet
    uint32_t now = (uint32_t) time(NULL);
    bc_uplink_t uplink;
    uplink_init(&uplink);
    // dot11
    wifi_mac             (uplink.dot11.source);
    dot11_set_destination(&uplink.dot11, MAC_BROADCAST);
    dot11_set_bssid      (&uplink.dot11, MAC_EBCS(0x01, 0x02, 0x03));
    // action and base
    action_set_category(&uplink.action, ACTION_CATEGORY_PUBLIC);
    base_set_action    (&uplink.base,   ACTION_VALUE_UPLINK);
    // uplink fields
    static const uint8_t uri[]       = "localhost:1112";
    static const uint8_t payload[]   = "Hello World!";
    static const uint8_t signature[] = "";
    uplink_set_tx_time  (&uplink, now);
    uplink_set_uri      (&uplink, uri,       (sizeof(uri)       - 1));
    uplink_set_payload  (&uplink, payload,   (sizeof(payload)   - 1));
    uplink_set_signature(&uplink, signature, (sizeof(signature) - 1), SIGNATURE_TYPE_HLSA);
    // transmit uplink packet
    uint8_t *bytes;
    size_t   size;
    uplink_bytes(&uplink, &bytes, &size);
    esp_wifi_80211_tx(WIFI_IF_STA, bytes, size, true);
    uplink_free(&bytes);
}
