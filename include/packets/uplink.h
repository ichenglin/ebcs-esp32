#ifndef UPLINK_H
#define UPLINK_H

#include <stdint.h>

#include "packets/dot11.h"
#include "packets/action.h"
#include "packets/base.h"

typedef struct {
    uint8_t certificate_present : 1;
    uint8_t tx_time_present     : 1;
    uint8_t count_present       : 1;
    uint8_t signature_type      : 3;
} bc_uplink_flags_t;

typedef struct {
    // header
          dot11_t           dot11;
          action_t          action;
          bc_base_t         base;
	// uplink
          bc_uplink_flags_t flags;
    const uint8_t          *uri;
          uint8_t           uri_len;
    const uint8_t          *payload;
          uint16_t          payload_len;
    const uint8_t          *certificate;
          uint16_t          certificate_len;
          uint32_t          frame_tx_time;
          uint64_t          frame_count;
    const uint8_t          *signature;
          uint16_t          signature_len;
} bc_uplink_t;

bc_uplink_t *uplink_new            ();
void         uplink_free           (bc_uplink_t *uplink);
bool         uplink_set_uri        (bc_uplink_t *uplink, const uint8_t *uri,         uint8_t uri_len);
bool         uplink_set_payload    (bc_uplink_t *uplink, const uint8_t *payload,     uint16_t payload_len);
bool         uplink_set_certificate(bc_uplink_t *uplink, const uint8_t *certificate, uint16_t certificate_len);
bool         uplink_set_signature  (bc_uplink_t *uplink, const uint8_t *signature,   uint16_t signature_len, uint8_t type);
void         uplink_set_tx_time    (bc_uplink_t *uplink, uint32_t tx_time);
void         uplink_set_count      (bc_uplink_t *uplink, uint64_t count);
bool         _uplink_set_bytes     (const uint8_t **pointer_old, const uint8_t *pointer_new, size_t pointer_new_size);

#endif // UPLINK_H