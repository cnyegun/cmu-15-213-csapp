	.file	"dw_loop.c"
	.text
	.globl	dw_loop
	.type	dw_loop, @function
dw_loop:
.LFB0:
	.cfi_startproc
	movabsq	$2049638230412172402, %rdx
	movq	%rdi, %rax
	imulq	%rdx
	movq	%rdi, %rax
	sarq	$63, %rax
	subq	%rax, %rdx
	leaq	0(,%rdi,4), %rcx
	.p2align 4
.L2:
	leaq	5(%rdx,%rdi), %rdi
	subq	$2, %rcx
	testq	%rcx, %rcx
	jg	.L2
	movq	%rdi, %rax
	ret
	.cfi_endproc
.LFE0:
	.size	dw_loop, .-dw_loop
	.ident	"GCC: (GNU) 15.2.1 20251211 (Red Hat 15.2.1-5)"
	.section	.note.GNU-stack,"",@progbits
