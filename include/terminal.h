#ifndef TERMINAL_H
#define TERMINAL_H

#include <types.h>

u8 terminal_slow;

void terminal_initialize();
 
void terminal_setcolor(uint8_t color);
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
 
void terminal_putchar(char c);
 
void terminal_writestring(const char* data);

void terminal_writenibble(unsigned char n);

void terminal_writeu32(unsigned long d);

void terminal_newline();

void terminal_writenum(u32 num);

void terminal_scroll();

void terminal_hexdump(void *ptr, int len);

#endif

