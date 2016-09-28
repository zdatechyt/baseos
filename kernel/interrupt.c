#include <interrupts.h>
#include <types.h>
#include <irq.h>
#include <asm.h>
#include <pic.h>

// Initializes IDTR structure
void kernel_init_idt() {
	u32 *idtr_ptr;
	u16 *idtr_len;

	idtr_len = (u16*)(&(kidtr[0]));
	idtr_ptr = (u32*)(&(kidtr[2]));
	*(idtr_ptr) = (u32)&kidt;
	*(idtr_len) = (u16)sizeof(struct IDT)*256; 
	}

// Sets an interrupt descriptor in the IDT
void interrupt_set(unsigned char num, void *offset, unsigned short selector, unsigned char type_attr) {
	kidt[num].offset_1=(((unsigned int)offset)&0xffff);
	kidt[num].selector=selector;
	kidt[num].zero=0;
	kidt[num].type_attr=type_attr;
	kidt[num].offset_2=((((unsigned int)offset)>>16)&0xffff);
	}

// Installs system interrupts
void interrupts_install() {	
	interrupt_set(0x0D,exception_gpf,get_cs(),IDT_TYPE_ATTR(1,0,0,GT_32INT)); // copy and paste interrupt_set lines to install interrupts. just change the pointer to the handler
	interrupt_set(0x08,exception_double_fault,get_cs(),IDT_TYPE_ATTR(1,0,0,GT_32INT));
	pic_init();
	ints_enabled=1;
	}

