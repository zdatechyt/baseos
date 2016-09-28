#ifndef UTIL_H
#define UTIL_H

#include <types.h>

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

char itoa_buffer[50];

size_t strlen(const char* str);
char *itoa(long n);
void blkcpy(void* dstptr, const void* srcptr, size_t size);
int blkcmp(const void* aptr, const void* bptr, size_t size);

#endif

