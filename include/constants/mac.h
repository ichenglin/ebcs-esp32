#ifndef MAC_CONST_H
#define MAC_CONST_H

#define MAC_BROADCAST ((uint8_t[]) {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF})
#define MAC_EBCS(...) ((uint8_t[]) {0x01, 0x0F, 0xAC, __VA_ARGS__})

#endif // MAC_CONST_H