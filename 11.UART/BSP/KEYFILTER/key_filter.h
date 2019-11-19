#ifndef __KEY_FILTER_H
#define __KEY_FILTER_H

#include "imx6ull.h"


void key_filter_init(void);
void filtertimer_init(unsigned int prescalar,unsigned int Load_Value);
void filtertimer_stop(void);
void filtertimer_restart(unsigned int value);
void Irq_Epit2_keyfilter__Hander(unsigned int gicciar ,void *param);
void keyfilter_gpio1_16_31_irqhandler (void);



#endif // !__KEY_FILTER_H

