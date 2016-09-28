.text
/* filename: irq.s */

/* irqs */

.globl   irq_pit
.align   4
 
irq_pit:
    pushal
    cld /* C code following the sysV ABI requires DF to be clear on function entry */
    call pit_irq
    popal
    iret

.globl   irq_keyboard
.align   4
 
irq_keyboard:
    pushal
    cld /* C code following the sysV ABI requires DF to be clear on function entry */
    call kbd_irq
    popal
    iret


/* SW interrupts */


/* Exceptions */

.globl	exception_gpf
.align	4

exception_gpf:
    cld
    call kernel_gpf
    iret

.globl  exception_double_fault
.align  4

exception_double_fault:
    cld
    call kernel_dblflt
    iret

