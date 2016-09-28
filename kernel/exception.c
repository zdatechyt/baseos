#include <terminal.h>
#include <types.h>

u8 mute_exceptions=0;

// Handles and debugs GPFs
void kernel_gpf(u32 errorcode) {
	if (mute_exceptions==1) return;
	terminal_writestring("GENERAL PROTECTION FAULT: ");
	terminal_writeu32(errorcode);
	terminal_writestring("E: ");
	terminal_writeu32(errorcode&1);
	terminal_writestring(" Tbl: ");
	terminal_writeu32((errorcode>>1)&3);
	terminal_writestring(" Idx: ");
	terminal_writeu32((errorcode>>3)&0x1fff);
	terminal_newline();
	mute_exceptions=1;
	}

// Handles and debugs double faults
void kernel_dblflt(u32 errorcode) {
	if (mute_exceptions==1) return;
	terminal_writestring("!! !! D0U8L3 FAULT !! !!");
	terminal_newline();
	mute_exceptions=1;
	}

