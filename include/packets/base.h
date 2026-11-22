#ifndef BASE_H
#define BASE_H

#include <stdint.h>

typedef struct __attribute__((packed)) {
    uint8_t action;
} bc_base_t;

void base_set_action(bc_base_t *base, uint8_t action);

#endif // BASE_H