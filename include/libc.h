#ifndef LIBC_H
#define LIBC_H

#include "common.h"

extern void memset_u8(u8* dest, u8 value, SIZE_TYPE length);
extern void memset_u16(u16* dest, u16 value, SIZE_TYPE length);
extern void memset_u32(u32* dest, u32 value, SIZE_TYPE length);
extern void memset_u64(u64* dest, u64 value, SIZE_TYPE length);

extern void memcpy_u8(u8* dest, u8* src, SIZE_TYPE length);
extern void memcpy_u16(u16* dest, u16* src, SIZE_TYPE length);
extern void memcpy_u32(u32* dest, u32* src, SIZE_TYPE length);
extern void memcpy_u64(u64* dest, u64* src, SIZE_TYPE length);

// handwritten
extern void memset_fast_8(u64* dest, u8 value, SIZE_TYPE length);
extern void memset_fast_16(u64* dest, u16 value, SIZE_TYPE length);
extern void memset_fast_32(u64* dest, u32 value, SIZE_TYPE length);
extern void memset_fast_64_(u64* dest, SIZE_TYPE length, u64 value);

// Macros so that we have consistent argument order
#define memset_fast_64(DEST, VALUE, LENGTH) memset_fast_64_(DEST, LENGTH, VALUE)

#endif

