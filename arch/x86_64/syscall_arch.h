#define __SYSCALL_LL_E(x) (x)
#define __SYSCALL_LL_O(x) (x)

#include <cardinal/syscall_emu.h>

static __inline long __syscall0(long n)
{
	return (long)SyscallEmu0((unsigned int)n);
}

static __inline long __syscall1(long n, long a1)
{
	return (long)SyscallEmu1((unsigned int)n, (unsigned long)a1);
}

static __inline long __syscall2(long n, long a1, long a2)
{
	return (long)SyscallEmu2((unsigned int)n, (unsigned long)a1, (unsigned long)a2);
}

static __inline long __syscall3(long n, long a1, long a2, long a3)
{
	return (long)SyscallEmu3((unsigned int)n, (unsigned long)a1, (unsigned long)a2, (unsigned long)a3);
}

static __inline long __syscall4(long n, long a1, long a2, long a3, long a4)
{
	return (long)SyscallEmu4((unsigned int)n, (unsigned long)a1, (unsigned long)a2, (unsigned long)a3, (unsigned long)a4);
}

static __inline long __syscall5(long n, long a1, long a2, long a3, long a4, long a5)
{
	return (long)SyscallEmu5((unsigned int)n, (unsigned long)a1, (unsigned long)a2, (unsigned long)a3, (unsigned long)a4, (unsigned long)a5);
}

static __inline long __syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6)
{
	return (long)SyscallEmu6((unsigned int)n, (unsigned long)a1, (unsigned long)a2, (unsigned long)a3, (unsigned long)a4, (unsigned long)a5, (unsigned long)a6);
}

#define VDSO_USEFUL
#define VDSO_CGT_SYM "__vdso_clock_gettime"
#define VDSO_CGT_VER "LINUX_2.6"
