#include <stdint.h>
#include <string.h>

#include "packets/dot11.h"

void _dot11_set_bytes(uint8_t *field, const uint8_t *bytes, size_t length);

void dot11_init(dot11_t *dot11) {
    *dot11 = (dot11_t){0};
}

uint8_t dot11_get_protocol(dot11_t *dot11) {
    return dot11->frame_control & 0x03;
}

uint8_t dot11_get_type(dot11_t *dot11) {
    return (dot11->frame_control >> 2) & 0x03;
}

uint8_t dot11_get_subtype(dot11_t *dot11) {
    return (dot11->frame_control >> 4) & 0x0F;
}

void dot11_set_protocol(dot11_t *dot11, uint8_t protocol) {
    dot11->frame_control = (dot11->frame_control & ~(0x03)) | (protocol & 0x03);
}

void dot11_set_type(dot11_t *dot11, uint8_t type) {
    dot11->frame_control = (dot11->frame_control & ~(0x03 << 2)) | ((type & 0x03) << 2);
}

void dot11_set_subtype(dot11_t *dot11, uint8_t subtype) {
    dot11->frame_control = (dot11->frame_control & ~(0x0F << 4)) | ((subtype & 0x0F) << 4);
}

void dot11_set_destination(dot11_t *dot11, const uint8_t *mac) {
    _dot11_set_bytes(dot11->destination, mac, 6);
}

void dot11_set_source(dot11_t *dot11, const uint8_t *mac) {
    _dot11_set_bytes(dot11->source, mac, 6);
}

void dot11_set_bssid(dot11_t *dot11, const uint8_t *mac) {
    _dot11_set_bytes(dot11->bssid, mac, 6);
}

void _dot11_set_bytes(uint8_t *field, const uint8_t *bytes, size_t length) {
    memcpy(field, bytes, length);
}