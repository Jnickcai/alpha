#ifndef __LED_H

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

#define __LED_H

 /* 定义按键值 */
enum keyvalue
{
    KEY_NONE = 0,
    KEY0_VALUE,
 };

void key_init(void);
int key_getvalue(void);

#endif // !_LED_H