#include <types.h>
#include <vga.h>
#include <io.h>
#include <util.h>

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
char terminal_hexchars[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void terminal_initialize() {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}

void *terminal_get_line_address(int ln) {
	return terminal_buffer+(ln*(VGA_WIDTH));
	}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_scroll() {
	for (int i=1; i<VGA_HEIGHT; i++) {
		blkcpy(terminal_get_line_address(i-1),terminal_get_line_address(i),VGA_WIDTH);
		}
	for (int j=0; j<VGA_WIDTH; j++) {
		terminal_putentryat(' ',terminal_color,j,VGA_HEIGHT-1);
		}
	}

void terminal_update_cursor(u16 row, u16 col) {
	u16 position=(row*80) + col;
 
	// cursor LOW port to vga INDEX register
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char)(position&0xFF));
	// cursor HIGH port to vga INDEX register
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char )((position>>8)&0xFF));
}

void terminal_putchar(char c) {
	if (c=='\n') {
		terminal_row++;
		terminal_column=0;
		if (terminal_row==(VGA_HEIGHT-1)) {
			terminal_scroll();
			terminal_row=VGA_HEIGHT-2;
			}
		return;
		}
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	terminal_update_cursor(terminal_row, terminal_column+1);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT) {
			terminal_row = 0;
		}
	}
}

void terminal_writestring(const char* data) {
	size_t datalen = strlen(data);
	for (size_t i = 0; i < datalen; i++)
		terminal_putchar(data[i]);
}

void terminal_newline() {
	terminal_writestring("\n");
	}

void terminal_writenibble(unsigned char n) {
	n&=0xf;
	terminal_putchar(terminal_hexchars[n]);
	}

void terminal_writeu32(unsigned long d) {
	int skipZeros= 1;
	u8 nib;

	terminal_writestring("0x");
	for(int i=0;i<8;i++) {
		nib = (d>>((7-i)*4))&0xf;

		if (nib!=0) skipZeros=0;
		if (skipZeros==0) terminal_writenibble(nib);
		}
	if (skipZeros==1) {
		terminal_writenibble(0);
		}
	}


void terminal_hexdump_byte(u8 d) {
	u8 nib;

	for(int i=0;i<2;i++) {
		nib = (d>>((1-i)*4))&0xf;

		terminal_writenibble(nib);
		}
	}

void terminal_hexdump_row(void *ptr, int off, int len) {
	u8 *pca = (u8*)ptr;

	terminal_hexdump_byte(off);
	terminal_writestring(": ");
	for (int i=0;i<8;i++) {
		if (i<len) { 
			terminal_hexdump_byte(pca[off+i]);
			terminal_writestring(" ");
			} else {
			terminal_writestring("   ");
			}
		}
	for (int i=0;i<len;i++) {
		if (pca[off+i]=='\n') terminal_putchar('.');
		terminal_putchar(pca[off+i]);
		}
	terminal_newline();
	}

void terminal_hexdump(void *ptr, int len) {
	int full_lines = len/8;
	int pln_len = len%8;

	terminal_writeu32((u32)ptr);
	terminal_newline();
	for (int i=0; i<full_lines; i++) {
		terminal_hexdump_row(ptr,i*8,8);
		}
	terminal_hexdump_row(ptr,full_lines*8,pln_len);
	}
