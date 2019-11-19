#ifndef __EPIT_H
#define __EPIT_H

#include "imx6ull.h"

void Irq_Epit1_Hander(unsigned int gicciar ,void *param);
void epit_init(unsigned int prescalar,unsigned int Load_Value);

#endif // !__EPIT_H



