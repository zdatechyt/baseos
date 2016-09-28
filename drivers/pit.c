#include <pic.h>
#include <asm.h>

int pit_ticks_left=0;

// ISR for PIT IRQ
void pit_irq(void) {
	if (pit_ticks_left>0) {
		pit_ticks_left--;
		}
	pic_sendEOI(0);
	}

// Wait for number of PIT ticks. At default frequency, about 18 ticks happen per second.
void pit_wait_ticks(int ticks) {
	pit_ticks_left+=ticks;
	while (pit_ticks_left>0) {
		asm_hlt();
		}
	}

