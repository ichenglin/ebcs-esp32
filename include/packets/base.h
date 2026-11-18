#ifndef BASE_H
#define BASE_H

#include <stdint.h>

typedef struct __attribute__((packed)) {
    uint8_t action;
} bc_base_t;

#endif // BASE_H