#include <stdarg.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "pthread_impl.h"
#include "syscall.h"

int clone(int (*func)(void *), void *stack, int flags, void *arg, ...)
{
	va_list ap;
	pid_t *ptid, *ctid;
	void  *tls;

	va_start(ap, arg);
	ptid = va_arg(ap, pid_t *);
	tls  = va_arg(ap, void *);
	ctid = va_arg(ap, pid_t *);
	va_end(ap);

  	unsigned long volatile params[7];
  	params[0] = (unsigned long)func;
  	params[1] = (unsigned long)stack;
  	params[2] = (unsigned long)flags;
  	params[3] = (unsigned long)arg;
  	params[4] = (unsigned long)ptid;
  	params[5] = (unsigned long)ctid;
  	params[6] = (unsigned long)tls;

	return __syscall_ret(__syscall1(SYS_clone, params));
}
