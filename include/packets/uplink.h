#ifndef UPLINK_H
#define UPLINK_H

#include <stdint.h>

typedef struct {
          uint8_t  flags;
          uint8_t  signature_type;
    const uint8_t *uri;
          uint8_t  uri_len;
    const uint8_t *payload;
          uint16_t payload_len;
    const uint8_t *certificate;
          uint16_t certificate_len;
          uint32_t frame_tx_time;
          uint64_t frame_count;
    const uint8_t *signature;
          uint16_t signature_len;
} bc_uplink_t;

#endif // UPLINK_H