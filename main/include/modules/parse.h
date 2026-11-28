#ifndef PARSE_MODULE_H
#define PARSE_MODULE_H

#include <stdint.h>

const void *parse_header(const uint8_t **frame, size_t *length, size_t size);

#endif // PARSE_MODULE_H
