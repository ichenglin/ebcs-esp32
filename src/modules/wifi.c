#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "packets/action.h"
#include "packets/base.h"
#include "packets/dot11.h"
#include "packets/uplink.h"
#include "modules/parse.h"
#include "modules/wifi.h"

bool wifi_init(void) {
    if (nvs_flash_init()                != ESP_OK) return false;
    if (esp_netif_init()                != ESP_OK) return false;
    if (esp_event_loop_create_default() != ESP_OK) return false;
    wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
    if (esp_wifi_init(&config)                         != ESP_OK) return false;
    if (esp_wifi_set_mode(WIFI_MODE_STA)               != ESP_OK) return false;
    if (esp_wifi_start()                               != ESP_OK) return false;
    if (esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE) != ESP_OK) return false;
    return true;
}

bool wifi_promiscuous(void) {
    if (esp_wifi_set_promiscuous_rx_cb(wifi_promiscuous_callback) != ESP_OK) return false;
    if (esp_wifi_set_promiscuous(true)                            != ESP_OK) return false;
    return true;
}

void wifi_promiscuous_callback(void *buffer, wifi_promiscuous_pkt_type_t type) {
    // dot11 type
    if (type != WIFI_PKT_MGMT) return;
    // extract packet payload data and length
    const wifi_promiscuous_pkt_t *packet = buffer;
    const uint8_t                *frame  = packet->payload;
    size_t                        length = packet->rx_ctrl.sig_len;
    // extract headers
    const dot11_t        *dot11  = parse_header(&frame, &length, sizeof(dot11_t));
    const dot11_action_t *action = parse_header(&frame, &length, sizeof(dot11_action_t));
    const bc_base_t      *base   = parse_header(&frame, &length, sizeof(bc_base_t));
    const bc_uplink_t    *uplink = parse_header(&frame, &length, sizeof(bc_uplink_t));
    if (!dot11 || !action || !base || !uplink) return;
    // check dot11
    if (dot11_control_type   (dot11->frame_control) != DOT11_TYPE_MANAGEMENT) return;
    if (dot11_control_subtype(dot11->frame_control) != DOT11_SUBTYPE_ACTION)  return;
    ESP_LOGI("TEST", "passed!");
}