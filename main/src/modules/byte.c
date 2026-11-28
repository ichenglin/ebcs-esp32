#include <stdint.h>
#include <string.h>

#include "modules/byte.h"

void _byte_endian_big(uint8_t **position, const uint8_t *data, size_t size);

void byte_add(uint8_t **position, const uint8_t *data, size_t size, bool endian_big) {
    if (endian_big) _byte_endian_big(position,  data, size);
    else            memcpy          (*position, data, size);
    *position += size;
}

void _byte_endian_big(uint8_t **position, const uint8_t *data, size_t size) {
    for (size_t index = 0; index < size; index++) {
        (*position)[index] = data[size - 1 - index];
    }
}
