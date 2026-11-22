#include <stdlib.h>
#include <string.h>

#include "constants/action.h"
#include "constants/base.h"
#include "constants/dot11.h"
#include "constants/uplink.h"
#include "packets/dot11.h"
#include "packets/uplink.h"

void _uplink_set_certificate_present(bc_uplink_t    *uplink,      uint8_t        present);
void _uplink_set_tx_time_present    (bc_uplink_t    *uplink,      uint8_t        present);
void _uplink_set_count_present      (bc_uplink_t    *uplink,      uint8_t        present);
void _uplink_set_signature_type     (bc_uplink_t    *uplink,      uint8_t        present);
bool _uplink_set_bytes              (const uint8_t **pointer_old, const uint8_t *pointer_new, size_t pointer_new_size);

bc_uplink_t *uplink_new() {
    return (bc_uplink_t*) malloc(sizeof(bc_uplink_t));
}

void uplink_init(bc_uplink_t *uplink) {
    // dot11
    dot11_init        (&uplink->dot11);
    dot11_set_protocol(&uplink->dot11, DOT11_PROTOCOL_80211);
    dot11_set_type    (&uplink->dot11, DOT11_TYPE_MANAGEMENT);
    dot11_set_subtype (&uplink->dot11, DOT11_SUBTYPE_ACTION);
    // action and base
    uplink->action.category = ACTION_CATEGORY_PUBLIC;
    uplink->base.action     = ACTION_VALUE_UPLINK;
    // uplink
    uplink->flags           = 0;
    uplink->uri             = NULL;
    uplink->uri_len         = 0;
    uplink->payload         = NULL;
    uplink->payload_len     = 0;
    uplink->certificate     = NULL;
    uplink->certificate_len = 0;
    uplink->frame_tx_time   = 0;
    uplink->frame_count     = 0;
    uplink->signature       = NULL;
    uplink->signature_len   = 0;
    _uplink_set_certificate_present(uplink, FIELD_ABSENT);
    _uplink_set_tx_time_present    (uplink, FIELD_ABSENT);
    _uplink_set_count_present      (uplink, FIELD_ABSENT);
    _uplink_set_signature_type     (uplink, SIGNATURE_TYPE_HLSA);
}

void uplink_free(bc_uplink_t *uplink) {
    if (!uplink)             return;
    if (uplink->uri)         free((void*) uplink->uri);
    if (uplink->payload)     free((void*) uplink->payload);
    if (uplink->certificate) free((void*) uplink->certificate);
    if (uplink->signature)   free((void*) uplink->signature);
    free(uplink);
}

uint8_t uplink_get_certificate_present(bc_uplink_t *uplink) {
    return (uplink->flags >> 7) & 0x01;
}

uint8_t uplink_get_tx_time_present(bc_uplink_t *uplink) {
    return (uplink->flags >> 6) & 0x01;
}

uint8_t uplink_get_count_present(bc_uplink_t *uplink) {
    return (uplink->flags >> 5) & 0x01;
}

uint8_t uplink_get_signature_type(bc_uplink_t *uplink) {
    return (uplink->flags >> 2) & 0x07;
}

bool uplink_set_uri(bc_uplink_t *uplink, const uint8_t *uri, uint8_t uri_len) {
    if (!_uplink_set_bytes(&uplink->uri, uri, uri_len)) return false;
    uplink->uri_len = uri_len;
    return true;
}

bool uplink_set_payload(bc_uplink_t *uplink, const uint8_t *payload, uint16_t payload_len) {
    if (!_uplink_set_bytes(&uplink->payload, payload, payload_len)) return false;
    uplink->payload_len = payload_len;
    return true;
}

bool uplink_set_certificate(bc_uplink_t *uplink, const uint8_t *certificate, uint16_t certificate_len) {
    if (!_uplink_set_bytes(&uplink->certificate, certificate, certificate_len)) return false;
    _uplink_set_certificate_present(uplink, FIELD_PRESENT);
    uplink->certificate_len = certificate_len;
    return true;
}

bool uplink_set_signature(bc_uplink_t *uplink, const uint8_t *signature, uint16_t signature_len, uint8_t type) {
    if (!_uplink_set_bytes(&uplink->signature, signature, signature_len)) return false;
    _uplink_set_signature_type(uplink, type);
    uplink->signature_len = signature_len;
    return true;
}

void uplink_set_tx_time(bc_uplink_t *uplink, uint32_t tx_time) {
    _uplink_set_tx_time_present(uplink, FIELD_PRESENT);
    uplink->frame_tx_time         = tx_time;
}

void uplink_set_count(bc_uplink_t *uplink, uint64_t count) {
    _uplink_set_count_present(uplink, FIELD_PRESENT);
    uplink->frame_count         = count;
}

void _uplink_set_certificate_present(bc_uplink_t *uplink, uint8_t present) {
    uplink->flags = (uplink->flags & ~0x80) | ((present & 0x01) << 7);
}

void _uplink_set_tx_time_present(bc_uplink_t *uplink, uint8_t present) {
    uplink->flags = (uplink->flags & ~0x40) | ((present & 0x01) << 6);
}

void _uplink_set_count_present(bc_uplink_t *uplink, uint8_t present) {
    uplink->flags = (uplink->flags & ~0x20) | ((present & 0x01) << 5);
}

void _uplink_set_signature_type(bc_uplink_t *uplink, uint8_t present) {
    uplink->flags = (uplink->flags & ~0x1C) | ((present & 0x07) << 2);
}

bool _uplink_set_bytes(const uint8_t **pointer_old, const uint8_t *pointer_new, size_t pointer_new_size) {
    // cleanup
    if (*pointer_old) free((void*) *pointer_old);
    // replace
    *pointer_old = (uint8_t*) malloc(pointer_new_size);
    if (*pointer_old == NULL) return false;
    memcpy((void*) *pointer_old, pointer_new, pointer_new_size);
    return true;
}