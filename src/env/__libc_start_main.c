#include <elf.h>
#include <poll.h>
#include <fcntl.h>
#include <signal.h>
#include <cardinal/process.h>
#include <cardinal/thread.h>
#include "syscall.h"
#include "atomic.h"
#include "libc.h"

struct elf_setup_params {
  uint16_t ver;
  uint16_t size;
  uint16_t page_size;
  uint16_t argc;  
  uint64_t rnd_seed;
  uint64_t elf_entry_point;
  char argv[1];
};

void __init_tls(size_t *);

static void dummy(void) {}
weak_alias(dummy, _init);

__attribute__((__weak__, __visibility__("hidden")))
extern void (*const __init_array_start)(void), (*const __init_array_end)(void);

static void dummy1(void *p) {}
weak_alias(dummy1, __init_ssp);


#define AUX_CNT 38
static size_t auxv_internal[AUX_CNT];

static int argc_int = 0;
static char **argv_int = NULL;

void __init_libc(void *args)
{
	size_t i, *auxv;

	struct elf_setup_params *init_params = (struct elf_setup_params*)args;
	argc_int = (int)init_params->argc;
	argv_int = (char**)init_params->argv;
	
	const char *pn = (const char*)init_params->argv;
	
	__environ = NULL;
	libc.auxv = auxv = (void*)auxv_internal;

	for(i = 0; i < AUX_CNT; i++)
		auxv_internal[i] = 0;

	auxv_internal[AT_RANDOM] = (size_t)init_params->rnd_seed;
	auxv_internal[AT_ENTRY] = (size_t)init_params->elf_entry_point;
	auxv_internal[AT_UID] = auxv_internal[AT_EUID] = (size_t)GetCurrentThreadUID();
	auxv_internal[AT_GID] = auxv_internal[AT_EGID] = (size_t)GetCurrentProcessUID();
	auxv_internal[AT_PAGESZ] = (size_t)init_params->page_size;

	__hwcap = auxv_internal[AT_HWCAP];
	__sysinfo = auxv_internal[AT_SYSINFO];
	libc.page_size = auxv_internal[AT_PAGESZ];


	if (pn) {
		__progname = __progname_full = pn;
		for (i=0; pn[i]; i++) if (pn[i]=='/') __progname = pn+i+1;
	}

	__init_tls(auxv_internal);
	__init_ssp((void *)auxv_internal[AT_RANDOM]);


	libc.secure = 1;
}

static void libc_start_init(void)
{
	_init();
	uintptr_t a = (uintptr_t)&__init_array_start;
	for (; a<(uintptr_t)&__init_array_end; a+=sizeof(void(*)()))
		(*(void (**)())a)();
}

weak_alias(libc_start_init, __libc_start_init);

int __libc_start_main(int (*main)(int,char **,char **), void *args)
{
	__init_libc(args);
	__libc_start_init();

	/* Pass control to the application */
	int retVal = main(argc_int, argv_int, NULL);
	exit(retVal);
	return 0;
}
