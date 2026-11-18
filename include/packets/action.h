#ifndef ACTION_H
#define ACTION_H

#include <stdint.h>

#define ACTION_CATEGORY_PUBLIC 0x4

typedef struct __attribute__((packed)) {
    uint8_t category;
} dot11_action_t;

#endif // ACTION_H