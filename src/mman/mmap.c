#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdint.h>
#include <limits.h>
#include "syscall.h"
#include "libc.h"

#include <cardinal/mem/server.h>
#include <cardinal/cardinal_types.h>

static void dummy(void) { }
weak_alias(dummy, __vm_wait);

#define UNIT SYSCALL_MMAP2_UNIT
#define OFF_MASK ((-0x2000ULL << (8*sizeof(long)-1)) | (UNIT-1))

void *__mmap(void *start, size_t len, int prot, int flags, int fd, off_t off)
{
	if (off & OFF_MASK) {
		errno = EINVAL;
		return MAP_FAILED;
	}
	if (len >= PTRDIFF_MAX) {
		errno = ENOMEM;
		return MAP_FAILED;
	}

	MMapFlags mmap_flags = MMapFlags_None;
	if (flags & MAP_FIXED) {
		__vm_wait();
		mmap_flags |= MMapFlags_Fixed;
	}

	if(MMap(&start,
    	 len,
     	 MemoryAllocationFlags_User | MemoryAllocationFlags_Present | MemoryAllocationFlags_Read | MemoryAllocationFlags_Write,
    	 mmap_flags,
    	 CachingModeWriteBack) != MemoryAllocationErrors_None)
	{
		errno = ENOMEM;
		return MAP_FAILED;
	}

	return start;
}

weak_alias(__mmap, mmap);

LFS64(mmap);
