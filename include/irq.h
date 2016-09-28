#ifndef IRQ_H
#define IRQ_H

void irq_keyboard(void);
void irq_pit(void);
void exception_gpf(u32 ec);
void exception_double_fault(u32 ec);

#endif

