#ifndef WIFI_H
#define WIFI_H

bool wifi_init       (uint8_t               channel);
bool wifi_promiscuous(wifi_promiscuous_cb_t callback);

#endif // WIFI_H
