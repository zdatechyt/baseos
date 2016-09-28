#include <vga.h>
#include <types.h>
 
// Makes VGA text-mode color byte
uint8_t make_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}
 
// Makes a VGA text-mode 16-bit entry
uint16_t make_vgaentry(char c, uint8_t color) {
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

