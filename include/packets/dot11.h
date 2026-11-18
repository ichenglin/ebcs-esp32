#ifndef DOT11_H
#define DOT11_H

#include <stdint.h>

#define DOT11_TYPE_MANAGEMENT 0x0
#define DOT11_SUBTYPE_ACTION  0xD

typedef struct __attribute__((packed)) {
    uint16_t frame_control;
    uint16_t duration;
    uint8_t  destination[6];
    uint8_t  source[6];
    uint8_t  bssid[6];
    uint16_t sequence_control;
} dot11_t;

// frame control fields
uint8_t dot11_control_protocol(uint16_t frame_control);
uint8_t dot11_control_type    (uint16_t frame_control);
uint8_t dot11_control_subtype (uint16_t frame_control);

#endif // DOT11_H