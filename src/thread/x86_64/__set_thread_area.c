#include <stdint.h>
#include "syscall.h"
#include "libc.h"

int __set_thread_area(void *p)
{
	return __syscall2(SYS_arch_prctl, 0x1002 /*ARCH_SET_FS*/, p);
}
