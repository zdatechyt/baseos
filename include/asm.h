#ifndef ASM_H
#define ASM_H

#include <types.h>

static inline u16 get_cs()
{
    u16 rv;
    asm ( "movw %%cs,%0" : "=a"(rv));

    return rv;
}

static inline void asm_hlt()
{
    asm ( "hlt;");
}

#endif

