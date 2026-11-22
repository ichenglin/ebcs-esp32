#ifndef WIFI_H
#define WIFI_H

#include "esp_wifi.h"

bool wifi_init       (uint8_t               channel);
bool wifi_promiscuous(wifi_promiscuous_cb_t callback);
bool wifi_mac        (uint8_t              *mac);

#endif // WIFI_H
