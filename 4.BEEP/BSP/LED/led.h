#ifndef __LED_H

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

#define __LED_H

#define ON  1
#define OFF 0

/*
* IOMUX regiseter address
*/
#define SW_MUX_GPIO1_IO03  *((volatile unsigned int *)0X020E0068)
#define SW_PAD_GPIO1_IO03 *((volatile unsigned int *)0X020E02F4)
/*
* GPIO1 regiseter address
*/
#define GPIO1_DR *((volatile unsigned int *)0X0209C000)
#define GPIO1_GDIR *((volatile unsigned int *)0X0209C004)
#define GPIO1_PSR *((volatile unsigned int *)0X0209C008)
#define GPIO1_ICR1 *((volatile unsigned int *)0X0209C00C)
#define GPIO1_ICR2 *((volatile unsigned int *)0X0209C010)
#define GPIO1_IMR *((volatile unsigned int *)0X0209C014)
#define GPIO1_ISR *((volatile unsigned int *)0X0209C018)
#define GPIO1_EDGE_SEL *((volatile unsigned int *)0X0209C01C)



void led_init(void);

void Switch_Led (int status);

#endif // !_LED_H


