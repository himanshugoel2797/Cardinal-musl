.global __syscall
.hidden __syscall
.type __syscall,@function
__syscall:
	movq 8(%rsp), %rax
	sub $0x30, %rsp
	movq %rsi,(%rsp)
	movq %rdi,%rsi
	movq %rdx,0x8(%rsp)
	movq %rcx,0x10(%rsp)
	movq %r8,0x18(%rsp)
	movq %r9,0x20(%rsp)
	movq %rax,0x28(%rsp)
	movq %rsp, %rdx
	movq 0x6, %rdi
	syscall
	movq %rsi, %rax
	add $0x30, %rsp
	ret
