#pragma once
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

#define k_printf kernel_printf
void kernel_printf(const char * msg, ...);
char * str_rev(char * str, int n);
size_t str_len(const char * msg);
void * memcpy(void * dst, const void * src, size_t n);
void * memset(void * str, int c, size_t n);