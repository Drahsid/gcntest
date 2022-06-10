#include "ControllerContext.h"
#include "main.h"
#include "libc.h"
#include "usb/debug.h"

char gButtonNames[BUTTONS_COUNT][8] = {
    "CR",
    "CL",
    "CD",
    "CU",
    "RT",
    "LT",
    "X",
    "Y",
    "DR",
    "DL",
    "DD",
    "DU",
    "ST",
    "Z",
    "B",
    "A",
};

char gControllerTypeNames[2][8] = {
    "N64",
    "GCN"
};

ControllerCtx gControllerContext;

void ControllerCtx_Construct(ControllerCtx* thisx) {
    memset_u8(thisx, 0, sizeof(ControllerCtx));

    osCreateMesgQueue(&thisx->serialMessageQ, &thisx->serialMsgBuf, 1);
    osSetEventMesg(OS_EVENT_SI, &thisx->serialMessageQ, 1);
}

void ControllerCtx_Init(ControllerCtx* thisx) {
    if (osContInit(&thisx->serialMessageQ, &thisx->valid, &thisx->status)) {
        debug_printf("osContInit failed?\n");
    }
    thisx->controllerMsg.type = CONTROLLER_DONE_MSG;
    osSetEventMesg(OS_EVENT_SI, &gGfxQ, (OSMesg)&thisx->controllerMsg);
}

void ControllerCtx_Step(ControllerCtx* thisx, f32 runtime) {
    OSTime time = osGetTime();
    u32 qndex;
    u32 index;
    u32 mask;
    u32 state;
    OSContPad* current;
    Controller* cont;

    for (qndex = 0; qndex < CONTROLLER_COUNT; qndex++) {
        if ((thisx->valid >> qndex) & 1) {
            current = &thisx->data[qndex];
            if (!current->errno) {
                cont = &thisx->controllers[qndex];
                cont->jx = current->stick_x;
                cont->jy = current->stick_y;
                cont->cx = current->c_stick_x;
                cont->cy = current->c_stick_y;
                cont->jxf = (f32)cont->jx * 0.02083333395f;
                cont->jyf = (f32)cont->jy * 0.02083333395f;

                if (osContGetType(qndex) == CONT_TYPE_GCN) {
                    cont->cxf = (f32)cont->cx * 0.02083333395f;
                    cont->cyf = (f32)cont->cy * 0.02083333395f;

                    if (cont->cxf > 1) cont->cxf = 1;
                    if (cont->cxf < -1) cont->cxf = -1;
                    if (cont->cyf > 1) cont->cyf = 1;
                    if (cont->cyf < -1) cont->cyf = -1;
                }

                if (cont->jxf > 1) cont->jxf = 1;
                if (cont->jxf < -1) cont->jxf = -1;
                if (cont->jyf > 1) cont->jyf = 1;
                if (cont->jyf < -1) cont->jyf = -1;

                for (index = 0; index < BUTTONS_COUNT; index++) {
                    mask = 1 << index;
                    state = current->button & mask;
                    if (state) {
                        // if the button is down, and was down
                        if (cont->buttons[index].state) {
                            // button was no longer just pressed
                            cont->buttons[index].flag &= ~(BUTTON_FLAG_RELEASED | BUTTON_FLAG_PRESSED);
                        }
                        else {
                            // button has been just pressed
                            cont->buttons_time[index].time = time;
                            cont->buttons_time[index].timef = runtime;
                            cont->buttons[index].flag |= BUTTON_FLAG_PRESSED;
                            cont->buttons[index].flag &= ~BUTTON_FLAG_RELEASED;
                        }
                        cont->buttons[index].state = 1;
                    }
                    else {
                        // if button is not down, and was down
                        if (cont->buttons[index].state) {
                            // button has been released
                            cont->buttons_time[index].time = 0;
                            cont->buttons_time[index].timef = 0;
                            cont->buttons[index].flag |= BUTTON_FLAG_RELEASED;
                            cont->buttons[index].flag &= ~BUTTON_FLAG_PRESSED;
                        }
                        else {
                            // button is idle
                            cont->buttons[index].flag &= ~(BUTTON_FLAG_RELEASED | BUTTON_FLAG_PRESSED);
                        }
                        cont->buttons[index].state = 0;
                    }
                }
            }
        }
    }
}

