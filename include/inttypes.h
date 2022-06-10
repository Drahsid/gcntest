#ifndef INTTYPES_H
#define INTTYPES_H

#include <PR/ultratypes.h>

/*
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;

typedef float f32;
typedef double f64;
*/

typedef u32 SIZE_TYPE;
typedef void* POINTER_TYPE;

#ifndef NULL
#define NULL 0
#endif

#ifndef NULLPTR
#define NULLPTR 0
#endif

#endif

