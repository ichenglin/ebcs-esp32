#ifndef BASE_H
#define BASE_H

#include <stdint.h>

#define ACTION_VALUE_UPLINK      0x33
#define ACTION_VALUE_INFO        0x34
#define ACTION_VALUE_TERMINATION 0x35

typedef struct __attribute__((packed)) {
    uint8_t action;
} bc_base_t;

#endif // BASE_H