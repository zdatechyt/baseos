#include <pic.h>
#include <asm.h>

int pit_ticks_left=0;

void pit_irq(void) {
	if (pit_ticks_left>0) {
		pit_ticks_left--;
		}
	pic_sendEOI(0);
	}

void pit_wait_ticks(int ticks) {
	pit_ticks_left+=ticks;
	while (pit_ticks_left>0) {
		asm_hlt();
		}
	}

