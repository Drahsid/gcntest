#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "common.h"

#define BASE_RES_X 320
#define BASE_RES_Y 240

#define RES_X (BASE_RES_X)
#define RES_Y (BASE_RES_Y)

#define FRAMEBUFFER_COUNT 2

enum {
    FRAMEBUFFER_INDEX_0 = 0,
    FRAMEBUFFER_INDEX_1,
    FRAMEBUFFER_INDEX_Z
};

extern u16* gFramebuffer[FRAMEBUFFER_COUNT + 1];
extern u16* gAuxFramebuffer[FRAMEBUFFER_COUNT + 1];
extern u16 gScreenResX;
extern u16 gScreenResY;
extern u16 gBaseScreenResX;
extern u16 gBaseScreenResY;

extern void FrameBuffer_SetViClosestMode(void);
extern s32 FrameBuffer_GetViClosestMode(void);
extern void FrameBuffer_SetViMode(u8 mode);

#endif

