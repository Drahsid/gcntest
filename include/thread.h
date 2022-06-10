#ifndef THREAD_H
#define THREAD_H

#include "common.h"

#define BASE_STACKSIZE 0x1000
#define BOOT_STACKSIZE BASE_STACKSIZE
#define MAIN_STACKSIZE (BASE_STACKSIZE * 64)

#define STACK_SECTION __attribute__((section(".stack")))

enum {
    THREAD_ID_IDLE = 1,
    THREAD_ID_MAIN
};

enum {
    THREAD_PRI_NONE = 0,
    THREAD_PRI_DEFAULT = 10
};

extern const SIZE_TYPE gStackSizeBoot; // needed to not harcode this in entrypoint
extern u8 gStackBoot[];
extern u8 gStackIdle[];
extern u8 gStackMain[];

extern OSThread gThreadIdle;
extern OSThread gThreadMain;

#endif

