#include <sys/mman.h>
#include "syscall.h"
#include "libc.h"


#include <cardinal/memory.h>
#include <cardinal/cardinal_types.h>

static void dummy(void) { }
weak_alias(dummy, __vm_wait);

int __munmap(void *start, size_t len)
{
	__vm_wait();
	return Unmap(start, len);
}

weak_alias(__munmap, munmap);
