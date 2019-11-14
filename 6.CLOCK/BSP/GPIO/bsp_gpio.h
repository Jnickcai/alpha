#ifndef __BSP_GPIO_H

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

#define __BSP_GPIO_H

typedef enum gpio_pin_level
{
    gpio_pin_level_hight    =   1u,
    gpio_pin_level_low      =   0u,
}gpio_pin_level_t;

typedef enum gpio_pin_direction
{
    gpio_pin_input  =   0u,
    gpio_pin_output =   1u,
}gpio_pin_direction_t;

/*GPIO 配置结构体*/
typedef struct gpio_pin_config
{
    gpio_pin_direction_t direction; //gpio引脚的方向 输入or输出
    gpio_pin_level_t     output_logic;           //如果是输出的话，默认输出电平
}gpio_pin_config_t;



void gpio_init(GPIO_Type *GPIO,int pin,gpio_pin_config_t *config);  //初始化GPIO
int gpio_read_pin(GPIO_Type *GPIO,int pin);     //读取GPIO电平
void gpio_writte_pin(GPIO_Type *GPIO,int pin,gpio_pin_level_t value);   //设置GPIO引脚输出电平



#endif //__BSP_GPIO_H