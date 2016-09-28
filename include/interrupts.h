#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <types.h>

#define GT_32TASK 5
#define GT_16INT 6
#define GT_16TRAP 7
#define GT_32INT 14
#define GT_32TRAP 15

#define IDT_TYPE_ATTR(p,dpl,s,gt) (((p&0x1)<<7)|((dpl&0x3)<<6)|((s&0x1)<<4)|(gt&0xf))

typedef u8 IDTR[6];

struct IDT {
	unsigned short offset_1;
	unsigned short selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short offset_2;
	};

IDTR kidtr;
struct IDT kidt[256];

u8 ints_enabled;

void kernel_init_idt();

void interrupt_set(unsigned char num, void *offset, unsigned short selector, unsigned char type_attr);

void interrupts_install();

#endif

