#ifdef APP_STATION

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"

#include "packets/action.h"
#include "packets/base.h"
#include "packets/dot11.h"
#include "packets/uplink.h"
#include "modules/mac.h"
#include "modules/parse.h"
#include "modules/wifi.h"

void app_sniff(void *buffer, wifi_promiscuous_pkt_type_t type);

static const char *TAG = "STATION";

void app_main(void) {
    vTaskDelay(pdMS_TO_TICKS(1000));
    if (!wifi_init(1))                { ESP_LOGE(TAG, "Failed to initialize Wi-Fi");             return; }
    if (!wifi_promiscuous(app_sniff)) { ESP_LOGE(TAG, "Failed to start Wi-Fi promiscuous mode"); return; }
    ESP_LOGI(TAG, "Wi-Fi promiscuous mode started successfully!");
}

void app_sniff(void *buffer, wifi_promiscuous_pkt_type_t type) {
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
    if (mac_bc               (dot11->bssid)         == false)                 return;
    // check action
    if (action->category != ACTION_CATEGORY_PUBLIC) return;
    if (base->action     != ACTION_VALUE_UPLINK)    return;
    ESP_LOGI(TAG, "passed!");
}

#endif