#ifndef __BSP_EXTI_H

#define __BSP_EXTI_H


#include "imx6ull.h"


void exit_init(void);
void GPIO1_IO18_irqhandler(unsigned int gicciar ,void *param);

#endif // 