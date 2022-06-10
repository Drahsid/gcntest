#ifndef LINKER_SYMBOLS_H
#define LINKER_SYMBOLS_H

#include "common.h"

extern u8 __code_start[];
extern u8 __code_start_rom[];
extern u8 __code_end[];
extern u8 __code_size[];
extern u8 __bss_start[];
extern u8 __bss_end[];
extern u8 __bss_size[];
extern u8 __stack_start[];
extern u8 __stack_end[];
extern u8 __stack_size[];
extern u8 __framebuffer_start[];
extern u8 __framebuffer_end[];
extern u8 __framebuffer_size[];

#endif

