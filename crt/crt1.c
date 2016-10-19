#include <features.h>

#define START "_start"

#include "crt_arch.h"

int main();
void _init() __attribute__((weak));
void _fini() __attribute__((weak));
_Noreturn int __libc_start_main(int (*)(), void*);

void _start_c(long *p)
{
	__libc_start_main(main, p);
}
