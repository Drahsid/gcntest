#ifndef CONTROLLERCTX_H
#define CONTROLLERCTX_H

#include "common.h"

#define CONTROLLER_COUNT (MAXCONTROLLERS)

enum {
    BUTTON_FLAG_PRESSED = (1 << 0),
    BUTTON_FLAG_RELEASED = (1 << 1)
};

enum {
    BUTTON_STATE_UP = 0,
    BUTTON_STATE_DOWN
};

enum {
    BUTTONS_CR = 0,
    BUTTONS_CL,
    BUTTONS_CD,
    BUTTONS_CU,
    BUTTONS_RT,
    BUTTONS_LT,
    BUTTONS_Y,
    BUTTONS_X,
    BUTTONS_DR,
    BUTTONS_DL,
    BUTTONS_DD,
    BUTTONS_DU,
    BUTTONS_ST,
    BUTTONS_Z,
    BUTTONS_B,
    BUTTONS_A,
    BUTTONS_COUNT
};

typedef struct {
#pragma pack(1)
    u8 state : 1;
    u8 flag : 2;
    u8 unused : 5;
#pragma pack()
} ButtonState;

typedef struct {
    OSTime time;
    f32 timef;
} ButtonTime;

typedef union {
    struct {
        f32 jf[2];
        f32 cf[2];
        s16 j[2];
        s16 c[2];
#pragma pack(1)
        ButtonState buttons[BUTTONS_COUNT];
#pragma pack(0)
        ButtonTime buttons_time[BUTTONS_COUNT];
    };
    struct {
        f32 jxf;
        f32 jyf;
        f32 cxf;
        f32 cyf;
        s16 jx;
        s16 jy;
        s16 cx;
        s16 cy;
#pragma pack(1)
        ButtonState cr;
        ButtonState cl;
        ButtonState cd;
        ButtonState cu;
        ButtonState rt;
        ButtonState lt;
        ButtonState x;
        ButtonState y;
        ButtonState dr;
        ButtonState dl;
        ButtonState dd;
        ButtonState du;
        ButtonState st;
        ButtonState z;
        ButtonState b;
        ButtonState a;
#pragma pack(0)
        ButtonTime cr_time;
        ButtonTime cl_time;
        ButtonTime cd_time;
        ButtonTime cu_time;
        ButtonTime rt_time;
        ButtonTime lt_time;
        ButtonTime x_time;
        ButtonTime y_time;
        ButtonTime dr_time;
        ButtonTime dl_time;
        ButtonTime dd_time;
        ButtonTime du_time;
        ButtonTime st_time;
        ButtonTime z_time;
        ButtonTime b_time;
        ButtonTime a_time;
    };
} Controller;

typedef struct {
    OSContStatus status[CONTROLLER_COUNT];
    OSContPad data[CONTROLLER_COUNT];
    Controller controllers[CONTROLLER_COUNT];
    OSScMsg controllerMsg;
    OSMesgQueue serialMessageQ;
    OSMesg serialMsgBuf;
    u32 blocking;
    u8 valid;
} ControllerCtx;

extern char gButtonNames[BUTTONS_COUNT][8];
extern char gControllerTypeNames[2][8];
extern ControllerCtx gControllerContext;

extern void ControllerCtx_Construct(ControllerCtx* thisx);
extern void ControllerCtx_Init(ControllerCtx* thisx);
extern void ControllerCtx_Step(ControllerCtx* thisx, f32 runtime);

#endif

