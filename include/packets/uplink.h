#ifndef UPLINK_PACKET_H
#define UPLINK_PACKET_H

#include <stdint.h>

#include "packets/dot11.h"
#include "packets/action.h"
#include "packets/base.h"

typedef struct {
    // header
          dot11_t   dot11;
          action_t  action;
          bc_base_t base;
	// uplink
          uint8_t   flags;
          uint8_t   uri_len;
    const uint8_t  *uri;
	      uint16_t  payload_len;
    const uint8_t  *payload;
	      uint16_t  certificate_len;
    const uint8_t  *certificate;
          uint32_t  frame_tx_time;
          uint64_t  frame_count;   // 6 bytes
          uint16_t  signature_len; // not part of the final packet
    const uint8_t  *signature;
} bc_uplink_t;

void         uplink_init                   (bc_uplink_t *uplink);
void         uplink_bytes                  (bc_uplink_t *uplink, uint8_t **bytes, size_t *size);
uint8_t      uplink_get_certificate_present(bc_uplink_t *uplink);
uint8_t      uplink_get_tx_time_present    (bc_uplink_t *uplink);
uint8_t      uplink_get_count_present      (bc_uplink_t *uplink);
uint8_t      uplink_get_signature_type     (bc_uplink_t *uplink);
bool         uplink_set_uri                (bc_uplink_t *uplink, const uint8_t *uri,         uint8_t  uri_len);
bool         uplink_set_payload            (bc_uplink_t *uplink, const uint8_t *payload,     uint16_t payload_len);
bool         uplink_set_certificate        (bc_uplink_t *uplink, const uint8_t *certificate, uint16_t certificate_len);
bool         uplink_set_signature          (bc_uplink_t *uplink, const uint8_t *signature,   uint16_t signature_len, uint8_t type);
void         uplink_set_tx_time            (bc_uplink_t *uplink, uint32_t tx_time);
void         uplink_set_count              (bc_uplink_t *uplink, uint64_t count);

#endif // UPLINK_PACKET_H
