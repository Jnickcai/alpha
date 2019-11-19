#include "bsp_exti.h"
#include "bsp_gpio.h"
#include "bsp_int.h"
#include "delay.h"
#include "beep.h"


/*初始化外部中断  GPIO1-IO18*/

void exit_init(void)
{

        gpio_pin_config_t key_config;

/* 1、初始化 IO 复用, 复用为 GPIO1_IO18 */
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

    key_config.direction = gpio_pin_input;
    key_config.int_mode  = kgpio_IntfailEgde;
    gpio_init(GPIO1,18,&key_config);

    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn );
    system_register_irqhandler(GPIO1_Combined_16_31_IRQn,GPIO1_IO18_irqhandler,NULL);   /*注册中断处理函数*/
    gpio_enable(GPIO1,18);
}

void GPIO1_IO18_irqhandler(unsigned int gicciar ,void *param)
{
    static unsigned char beep_state = 0;
    delay_ms(10);
    if (gpio_read_pin(GPIO1,18)==0)
    {
        beep_state = !beep_state;
        beep_switch(beep_state);
    }
    	gpio_clearintflags(GPIO1, 18); /* 清除中断标志位 */
}