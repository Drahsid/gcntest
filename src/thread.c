#include "thread.h"

const SIZE_TYPE gStackSizeBoot = BOOT_STACKSIZE; // needed to not harcode this in entrypoint
STACK_SECTION u8 gStackBoot[BOOT_STACKSIZE];
STACK_SECTION u8 gStackIdle[BOOT_STACKSIZE];
STACK_SECTION u8 gStackMain[MAIN_STACKSIZE];

OSThread gThreadIdle;
OSThread gThreadMain;
