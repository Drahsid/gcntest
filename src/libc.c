#include "libc.h"

void memset_u8(u8* dest, u8 value, SIZE_TYPE length) {
    while (length -= sizeof(value)) {
        *dest = value;
        dest++;
    }
}

void memset_u16(u16* dest, u16 value, SIZE_TYPE length) {
    while (length -= sizeof(value)) {
        *dest = value;
        dest++;
    }
}

void memset_u32(u32* dest, u32 value, SIZE_TYPE length) {
    while (length -= sizeof(value)) {
        *dest = value;
        dest++;
    }
}

void memset_u64(u64* dest, u64 value, SIZE_TYPE length) {
    while (length -= sizeof(value)) {
        *dest = value;
        dest++;
    }
}

void memcpy_u8(u8* dest, u8* src, SIZE_TYPE length) {
    while (length--) {
        *dest++ = *src++;
    }
}

void memcpy_u16(u16* dest, u16* src, SIZE_TYPE length) {
    while (length--) {
        *dest++ = *src++;
    }
}

void memcpy_u32(u32* dest, u32* src, SIZE_TYPE length) {
    while (length--) {
        *dest++ = *src++;
    }
}

void memcpy_u64(u64* dest, u64* src, SIZE_TYPE length) {
    while (length--) {
        *dest++ = *src++;
    }
}
