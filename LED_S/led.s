@  by  Nick      2019-11-05
@  by  Nick      2019-11-05
@  by  Nick      2019-11-05

.global _start  /* */

    _start :
    @ enable all system clock
        ldr r0,=0x020c4068  @CCGR0 register address
        ldr r1,=0xffffffff 
        str r1,[r0]         @write 0xffffffff to CCGR0 register

        ldr r0 ,=0x020c406c @CCGR1 register address
        str r1 ,[r0]        @write 0xffffffff to CCGR1 register

        ldr r0 ,=0x020c4070 @CCGR2 register address
        str r1 ,[r0]        @write 0xffffffff to CCGR2 register

        ldr r0 ,=0x020c4074 @CCGR3 register address
        str r1 ,[r0]        @write 0xffffffff to CCGR3 register

        ldr r0 ,=0x020c4078 @CCGR4 register address
        str r1 ,[r0]        @write 0xffffffff to CCGR4 register

        ldr r0 ,=0x020c407c @CCGR5 register address
        str r1 ,[r0]        @write 0xffffffff to CCGR5 register

        ldr r0 ,=0x020c4080 @CCGR6 register address
        str r1 ,[r0]        @write 0xffffffff to CCGR6 register

    @configure GPIO1 IO03 PIN to GPIO output

        ldr r0,=0x020e0068  @IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 register address
        ldr r1,=0x5
        str r1,[r0]         @write 0x5 to IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 register  |GPIO1_IO03 of instance: gpio1

    @Configure the electrical properties of gpio 
         /*
            *bit 16:0 HYS close
            *bit [15:14]: 00 100K Ohm Pull Down
            *bit [13]   : 0 kepper 
            *bit [12]   : 1 pull/keeper enable
            *bit [11]   : 0 Open Drain Disabled
            *bit [7:6]  : 10 speed 100Mhzr
            *bit [5:3]  : 110 R0/6 Drive Strength
            *bit [0]    : 0 Slow Slew Rate
        */
        ldr r0,=0x020e02f4  @IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 register address
        ldr r1,=0x10b0
        str r1,[r0]         @write 0x5 to IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 register 

    @configure GPIO direction register (GPIO1_GDIR)  register    

        ldr r0 ,=0x0209C004
        ldr r1 ,=0x00000008     @configure GPIO0_IO3 to output
        str r1,[r0]


        b main
    @configure GPIO data register (GPIOx_DR)  register  ,set output to high level
led_off:ldr r0 ,=0x0209C000
        ldr r1 ,=0x00000008
        str r1 ,[r0] 
        bx lr	

led_on: ldr r0 ,=0x0209C000
        ldr r1 ,=0x00000000
        str r1 ,[r0]
        bx lr

 delay: ldr r3 ,=0x300000
    loop:   sub r3, r3, #1
	         cmp r3, #0
	         BNE loop
             bx lr

main:   bl led_on
        bl delay
        bl led_off
        bl delay
        b main




        