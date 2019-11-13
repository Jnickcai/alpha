#ifndef __KEY_H

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

#define __KEY_H

 /* 定义按键值 */
enum keyvalue
{
    KEY_NONE = 0,
    KEY0_VALUE=1,
 };

void key_init(void);    //初始化按键pin
int key_getvalue(void); //获取按键状态

#endif // !_KEY_H