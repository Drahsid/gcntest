#ifndef MAIN_H
#define MAIN_H

#include "common.h"

// forward declarations
void entrypoint_main(void);
void IdleThreadFunction(void);
void MainThreadFunction(void);

extern OSMesgQueue gGfxQ;

#endif

