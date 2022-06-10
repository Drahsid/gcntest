#include "main.h"
#include "thread.h"
#include "framebuffer.h"
#include "ControllerContext.h"
#include "libc.h"
#include "usb/debug.h"

// data
static DATA_ALIGN16 STACK_SECTION u8 sSchedulerStack[OS_SC_STACKSIZE];

static OSSched sScheduler;
static OSMesgQueue* sShedQ;
static OSScClient sGfxClient;
OSMesgQueue gGfxQ;
static OSMesg sGfxMsgBuf[FRAMEBUFFER_COUNT * 4];
static u64 sFramecount;
static f32 sRuntime;

#define NUM_PI_MSGS 8
static OSMesg sPiMessages[NUM_PI_MSGS];
static OSMesgQueue sPiMessageQ;

static s32 sControllerIndex;

// forward declarations
void entrypoint_main(void);
void IdleThreadFunction(void);
void MainThreadFunction(void);
static void Step(void);

// code
void entrypoint_main(void) {
    // Initialize the hardware and software
    osInitialize();

    // Create the idle thread
    osCreateThread(&gThreadIdle, THREAD_ID_IDLE, IdleThreadFunction, NULLPTR, gStackIdle + BOOT_STACKSIZE, THREAD_PRI_NONE);
    osStartThread(&gThreadIdle);
}

void IdleThreadFunction(void) {
    osCreatePiManager(OS_PRIORITY_PIMGR, &sPiMessageQ, sPiMessages, NUM_PI_MSGS);

    debug_initialize();
    debug_printf("Hello, World!\n");  

    // Create the main thread
    osCreateThread(&gThreadMain, THREAD_ID_MAIN, MainThreadFunction, NULLPTR, gStackMain + MAIN_STACKSIZE, THREAD_PRI_DEFAULT);
    osStartThread(&gThreadMain);
    
    while(1);
}

void MainThreadFunction(void) {
    s32 mode;
    s32 gcn;

    debug_printf("Build date %s %s\n", __DATE__, __TIME__);

    mode = FrameBuffer_GetViClosestMode();
    osCreateMesgQueue(&gGfxQ, sGfxMsgBuf, FRAMEBUFFER_COUNT * 4);

    osCreateScheduler(&sScheduler, (SIZE_TYPE)sSchedulerStack + OS_SC_STACKSIZE, 12, mode, 1);
    osScAddClient(&sScheduler, &sGfxClient, &gGfxQ);
    sShedQ = osScGetCmdQ(&sScheduler);

    // setup controller stuff
    ControllerCtx_Construct(&gControllerContext);
    ControllerCtx_Init(&gControllerContext);

    osViSwapBuffer(gFramebuffer[0]);

    gcn = 0;
    for (mode = 0; mode < CONTROLLER_COUNT; mode++) {
        if (osContGetType(mode) == CONT_TYPE_GCN) {
            debug_printf("gcn controller at index %d\n", mode);
            gcn++;
        }
    }

    if (gcn == 0) {
        debug_printf("no gcn :C\n");
        while (1);
    }

    while (1) {
        Step();
    }
}


DATA_ALIGN16 static char sDebugPrintBuf[0x400];

static void Print_ControllerInfo(void) {
    s32 substate_changed = 0;
    s32 index;
    s32 conttype;
    Controller* cont;
    char* bufp = &sDebugPrintBuf[0];

    memset_u8(sDebugPrintBuf, 0, sizeof(sDebugPrintBuf));
    
    if (gControllerContext.controllers[0].lt.flag & BUTTON_FLAG_PRESSED) {
        sControllerIndex--;
        substate_changed = 1;
    }

    if (gControllerContext.controllers[0].rt.flag & BUTTON_FLAG_PRESSED) {
        sControllerIndex++;
        substate_changed = 1;
    }

    if (substate_changed) {
        if (sControllerIndex >= CONTROLLER_COUNT) {
            sControllerIndex = 0;
        }
        else if (sControllerIndex < 0) {
            sControllerIndex = CONTROLLER_COUNT - 1;
        }
    }

    cont = &gControllerContext.controllers[sControllerIndex];
    conttype = osContGetType(sControllerIndex);

    bufp += sprintf(bufp, "%d %s\n",
        sControllerIndex,
        gControllerTypeNames[conttype] // osContGetType will return 0 for n64 and 1 for gcn
    );

    // print joystick
    if (conttype == CONT_TYPE_GCN) {
        bufp += sprintf(bufp, "jx %d %.1f jy %d %.1f cx %d %.1f cy %d %.1f\n",
            cont->jx, cont->jxf,
            cont->jy, cont->jyf,
            cont->cx, cont->cxf,
            cont->cy, cont->cyf
        );
    }
    else {
        bufp += sprintf(bufp, "jx %d %.1f jy %d %.1f\n",
            cont->jx, cont->jxf,
            cont->jy, cont->jyf
        );
    }

    for (index = 0; index < BUTTONS_COUNT; index++) {
        bufp += sprintf(bufp, "%s s %X f %X t %X %.1f\n",
            gButtonNames[index], cont->buttons[index].state, cont->buttons[index].flag, cont->buttons_time[index].time, cont->buttons_time[index].timef
        );
    }

    bufp += sprintf(bufp, "\n\n\n\n\n");

    debug_printf(sDebugPrintBuf);
}

static void Step(void) {
    OSScMsg* msg = NULLPTR;
    char buf[0x40];

    osRecvMesg(&gGfxQ, &msg, OS_MESG_BLOCK);
    switch(msg->type) {
        case (OS_SC_RETRACE_MSG): {
            // blah blah you would do game logic here

            osViSetEvent(&sScheduler.interruptQ, 666, 3); // update at 20fps

            ControllerCtx_Step(&gControllerContext, sRuntime);

            // start reading controller if ready
            if (!gControllerContext.blocking) {
                gControllerContext.blocking = 1;
                osContStartReadData(&gGfxQ);
            }

            Print_ControllerInfo();

            // bogus
            sFramecount++;
            sRuntime = sFramecount * 0.016666667f;

            break;
        }
        case (OS_SC_DONE_MSG): {
            // blah blah you would do drawing here
            break;
        }
        case (OS_SC_PRE_NMI_MSG): {
            // stop rendering on reset
            break;
        }
        case (CONTROLLER_DONE_MSG): {
            osContGetReadData(&gControllerContext.data);
            gControllerContext.blocking = 0;
            break;
        }
        default: break;
    }
}

