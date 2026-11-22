#ifndef DOT11_PACKET_H
#define DOT11_PACKET_H

#include <stdint.h>

typedef struct __attribute__((packed)) {
    uint16_t frame_control;
    uint16_t duration;
    uint8_t  destination[6];
    uint8_t  source[6];
    uint8_t  bssid[6];
    uint16_t sequence_control;
} dot11_t;

void    dot11_init           (dot11_t *dot11);
uint8_t dot11_get_protocol   (dot11_t *dot11);
uint8_t dot11_get_type       (dot11_t *dot11);
uint8_t dot11_get_subtype    (dot11_t *dot11);
void    dot11_set_protocol   (dot11_t *dot11, uint8_t        protocol);
void    dot11_set_type       (dot11_t *dot11, uint8_t        type);
void    dot11_set_subtype    (dot11_t *dot11, uint8_t        subtype);
void    dot11_set_destination(dot11_t *dot11, const uint8_t *mac);
void    dot11_set_source     (dot11_t *dot11, const uint8_t *mac);
void    dot11_set_bssid      (dot11_t *dot11, const uint8_t *mac);

#endif // DOT11_PACKET_H
