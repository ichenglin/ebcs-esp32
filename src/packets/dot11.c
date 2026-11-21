#include <stdint.h>

#include "packets/dot11.h"

uint8_t dot11_get_protocol(uint16_t frame_control) {
    return frame_control & 0x03;
}

uint8_t dot11_get_type(uint16_t frame_control) {
    return (frame_control >> 2) & 0x03;
}

uint8_t dot11_get_subtype(uint16_t frame_control) {
    return (frame_control >> 4) & 0x0F;
}