#ifndef ACTION_H
#define ACTION_H

#include <stdint.h>

typedef struct __attribute__((packed)) {
    uint8_t category;
} action_t;

void action_set_category(action_t *action, uint8_t category);

#endif // ACTION_H