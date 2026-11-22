#ifndef BYTE_H
#define BYTE_H

void byte_add       (uint8_t **position, const uint8_t *data, size_t size, bool endian_big);
void byte_endian_big(uint8_t **position, const uint8_t *data, size_t size);

#endif // BYTE_H
