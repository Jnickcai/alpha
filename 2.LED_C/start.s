@  by  Nick      2019-11-05
@  by  Nick      2019-11-05
@  by  Nick      2019-11-05

.global _start  /* */

    _start :
   /*set CPU to SVC mode */
   mrs r0 ,cpsr
   bic r0 ,r0 ,#0x1f
   orr r0 ,r0 ,#0x13
   msr cpsr,r0

   /*set the SP  pointer to 0X80200000*/
   ldr sp ,=0X80200000
   b main





        