#ifndef _BEEP_H
#define _BEEP_H

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

#define ON  1
#define OFF 0

void beep_init(void);
void beep_switch(int status);

#endif