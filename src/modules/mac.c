#include <stdint.h>
#include <string.h>

#include "modules/mac.h"

bool mac_bc(const uint8_t mac[6]) {
    return (memcmp(mac, MAC_BC_HEADER, (sizeof(MAC_BC_HEADER) - 1)) == 0);
}