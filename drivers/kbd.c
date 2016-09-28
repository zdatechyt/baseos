#include <kbd.h>
#include <types.h>
#include <io.h>
#include <pic.h>

// ISR for Keyboard IRQ
void kbd_irq(void) {
	kbd_last_key = inb(0x60); // always read this port so you will get further IRQs
	kbd_fired = 1;
	pic_sendEOI(1); // tell PIC we're done with this IRQ
	}
