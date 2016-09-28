#include <kbd.h>
#include <types.h>
#include <io.h>
#include <pic.h>

void kbd_irq(void) {
	kbd_last_key = inb(0x60);
	kbd_fired = 1;
	pic_sendEOI(1);
	}

