#ifndef WIFI_H
#define WIFI_H

bool wifi_init(void);
bool wifi_promiscuous(void);
void wifi_promiscuous_callback(void *buf, wifi_promiscuous_pkt_type_t type);

#endif // WIFI_H
