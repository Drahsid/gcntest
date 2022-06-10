#ifndef COMMON_H
#define COMMON_H

#include <ultra64.h>
#include "PR/sched.h"
#include "inttypes.h"
#include "linker_symbols.h"

#define DATA_ALIGN64 __attribute__((aligned(64)))
#define DATA_ALIGN32 __attribute__((aligned(32)))
#define DATA_ALIGN16 __attribute__((aligned(16)))

#define OFFSETOF(TYPE, ELEMENT) ((SIZE_TYPE)&(((TYPE*)0)->ELEMENT))

#define MATH_PI (3.14159265358979323)
#define MATH_TAU (MATH_PI * 2.0)
#define MATH_HPI (MATH_PI * 0.5)

#define DEG2RAD (0.0174532925199433)
#define RAD2DEG (57.29577951308231)
#define S2RAD (0.0000958737992429)
#define S2DEG (0.0054931640625)
#define RAD2S (10430.37835047045)
#define DEG2S (182.0444444444444)

#define STOR(RHS) (S2RAD * RHS)
#define STOD(RHS) (S2DEG * RHS)
#define RTOS(RHS) (RAD2S * RHS)
#define DTOS(RHS) (DEG2S * RHS)
#define DTOR(RHS) (DEG2RAD * RHS)
#define RTOD(RHS) (RAD2DEG * RHS)

// If you ever need to explicitly truncate these
#define STORF(RHS) ((f32)S2RAD * RHS)
#define STODF(RHS) ((f32)S2DEG * RHS)
#define RTOSF(RHS) ((f32)RAD2S * RHS)
#define DTOSF(RHS) ((f32)DEG2S * RHS)
#define DTORF(RHS) ((f32)DEG2RAD * RHS)
#define RTODF(RHS) ((f32)RAD2DEG * RHS)

// CPU CLOCK 2 ...
#define CC2SEC  (2.13333333e-8) // seconds
#define CC2MSEC (2.13333333e-5) // miliseconds
#define CC2NSEC (2.13333333e-2) // microseconds
#define CC2USEC (2.13333333e+1) // nanoseconds

// RDP CLOCK 2 ...
#define RC2SEC  (16.0e-10) // seconds
#define RC2MSEC (16.0e-6) // miliseconds (may be wrong)
#define RC2NSEC (16.0e-3) // microseconds
#define RC2USEC (16.0e+0) // nanoseconds (may be wrong)

#undef OS_CYCLES_TO_NSEC
#undef OS_CYCLES_TO_USEC

#define OS_CYCLES_TO_SEC(LHS)   ((LHS) * CC2SEC)
#define OS_CYCLES_TO_MSEC(LHS)  ((LHS) * CC2MSEC)
#define OS_CYCLES_TO_NSEC(LHS)  ((LHS) * CC2NSEC)
#define OS_CYCLES_TO_USEC(LHS)  ((LHS) * CC2USEC)

#define OS_CYCLES_TO_SECLL(LHS)  (((u64)(c) * (1000000000000000LL / 15625000000000LL)) / (OS_CPU_COUNTER / 15625000000000LL))
#define OS_CYCLES_TO_MSECLL(LHS) (((u64)(c) * (1000000000000LL / 15625000000LL)) / (OS_CPU_COUNTER / 15625000000LL))
#define OS_CYCLES_TO_NSECLL(LHS) (((u64)(c) * (1000000000LL / 15625000LL)) / (OS_CPU_COUNTER / 15625000LL))
#define OS_CYCLES_TO_USECLL(LHS) (((u64)(c) * (1000000LL / 15625LL)) / (OS_CPU_COUNTER / 15625LL))

#define RDP_CYCLES_TO_SEC(LHS)  ((LHS) * RC2SEC)
#define RDP_CYCLES_TO_MSEC(LHS) ((LHS) * RC2MSEC)
#define RDP_CYCLES_TO_NSEC(LHS) ((LHS) * RC2NSEC)
#define RDP_CYCLES_TO_USEC(LHS) ((LHS) * RC2USEC)

#define RDP_CYCLES_TO_SECLL(LHS)  (((u64)(LHS) / 10000) / 625)
#define RDP_CYCLES_TO_MSECLL(LHS) (((u64)(LHS) / 10) / 625)
#define RDP_CYCLES_TO_NSECLL(LHS) (((u64)(LHS) << 2) / 125)
#define RDP_CYCLES_TO_USECLL(LHS) ((u64)(LHS) * 16)

enum {
    CONTROLLER_DONE_MSG = (OS_SC_LAST_MSG + 1),
};

#endif

