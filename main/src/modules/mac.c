#include <stdint.h>
#include <string.h>

#include "constants/mac.h"
#include "modules/mac.h"

bool mac_bc(const uint8_t mac[6]) {
    return (memcmp(mac, MAC_EBCS(), sizeof(MAC_EBCS())) == 0);
}
