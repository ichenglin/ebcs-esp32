#include <stdint.h>

#include "modules/parse.h"

const void *parse_header(const uint8_t **frame, size_t *length, size_t size) {
    if (*length < size) return NULL;
    // offset the frame pointer and length
    const void *result = *frame;
    *frame  += size;
    *length -= size;
    return result;
}