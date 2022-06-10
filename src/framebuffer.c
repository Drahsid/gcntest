#include "framebuffer.h"

#define FRAMEBUFFER_SECTION(NUM) __attribute__((section(".framebuffer." #NUM)))

// framebuffer stuff
FRAMEBUFFER_SECTION(0) u16 gFramebuffer0[RES_Y * RES_X];
FRAMEBUFFER_SECTION(1) u16 gFramebuffer1[RES_Y * RES_X];
FRAMEBUFFER_SECTION(2) u16 gFramebuffer2[RES_Y * RES_X]; // z

u16* gFramebuffer[FRAMEBUFFER_COUNT + 1] = {
    gFramebuffer0, gFramebuffer1, gFramebuffer2
};

// resolution stuff
u16 gScreenResX = RES_X;
u16 gScreenResY = RES_Y;
u16 gBaseScreenResX = RES_X;
u16 gBaseScreenResY = RES_Y;

void FrameBuffer_SetViClosestMode(void) {
    if (gBaseScreenResX == 640) {
        if (osTvType == OS_TV_NTSC) {
            osViSetMode(&osViModeTable[OS_VI_NTSC_HPF1]);
        }
        else if (osTvType == OS_TV_PAL) {
            osViSetMode(&osViModeTable[OS_VI_PAL_HPF1]);
        }
        else if (osTvType == OS_TV_MPAL) {
            osViSetMode(&osViModeTable[OS_VI_MPAL_HPF1]);
        }
        else {
            osViSetMode(&osViModeTable[OS_VI_NTSC_HPF1]);
        }
    }
    else {
        if (osTvType == OS_TV_NTSC) {
            osViSetMode(&osViModeTable[OS_VI_NTSC_LPN1]);
        }
        else if (osTvType == OS_TV_PAL) {
            osViSetMode(&osViModeTable[OS_VI_PAL_LPN1]);
        }
        else if (osTvType == OS_TV_MPAL) {
            osViSetMode(&osViModeTable[OS_VI_MPAL_LPN1]);
        }
        else {
            osViSetMode(&osViModeTable[OS_VI_NTSC_LPN1]);
        }
    }
}

s32 FrameBuffer_GetViClosestMode(void) {
    if (gBaseScreenResX == 640) {
        if (osTvType == OS_TV_NTSC) {
            return OS_VI_NTSC_HPF1;
        }
        else if (osTvType == OS_TV_PAL) {
            return OS_VI_PAL_HPF1;
        }
        else if (osTvType == OS_TV_MPAL) {
            return OS_VI_MPAL_HPF1;
        }
        else {
            return OS_VI_NTSC_HPF1;
        }
    }
    else {
        if (osTvType == OS_TV_NTSC) {
            return OS_VI_NTSC_LPN1;
        }
        else if (osTvType == OS_TV_PAL) {
            return OS_VI_PAL_LPN1;
        }
        else if (osTvType == OS_TV_MPAL) {
            return OS_VI_MPAL_LPN1;
        }
        else {
            return OS_VI_NTSC_LPN1;
        }
    }
}

void FrameBuffer_SetViMode(u8 mode) {
    osViSetMode(&osViModeTable[mode]);
}

