#include <terminal.h>
#include <interrupts.h>

// Main C function for the kernel
void kernel_main(void *mbh) {
	terminal_initialize();
	interrupts_install();
	terminal_writestring("Hello world!\n");
	terminal_writestring("https://github.com/zdatechyt/baseos\n");
	}
