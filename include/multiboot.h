#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <types.h>

typedef struct {
	u32 vbe_control_info;
	u32 vbe_mode_info;
	u32 vbe_mode;
	u32 vbe_interface_seg;
	u32 vbe_interface_off;
	u32 vbe_interface_len;
	} vbe_info_t;

typedef struct {
	u32 flags;
	u32 mem_lower;
	u32 mem_upper;
	u32 boot_device;
	u32 cmdline;
	u32 mods_count;
	u32 mods_addr;
	u32 syms[4];
	u32 mmap_length;
	u32 mmap_addr;
	u32 drives_length;
	u32 drives_addr;
	u32 config_table;
	u32 boot_loader_name;
	u32 apm_table;
	vbe_info_t vbe;
	} multiboot_header_raw_t;

void multiboot_parse(multiboot_header_raw_t *h);

void multiboot_debug(multiboot_header_raw_t *h);

void multiboot_debug_mmap(multiboot_header_raw_t *h);

#endif

