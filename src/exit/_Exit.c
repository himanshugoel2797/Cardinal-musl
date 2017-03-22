#include <stdlib.h>
#include "syscall.h"

#include <cardinal/proc/server.h>

_Noreturn void _Exit(int ec)
{
	ExitProcess(ec);
	while(1);
}
