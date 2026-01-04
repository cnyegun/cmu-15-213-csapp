	.file	"dw_loop.c"
	.text
	.globl	dw_loop
	.type	dw_loop, @function
dw_loop:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rcx
	movabsq	$2049638230412172402, %rdx
	movq	%rcx, %rax
	imulq	%rdx
	movq	%rdx, %rsi
	sarq	$63, %rcx
	movq	%rcx, %rdx
	movq	%rsi, %rax
	subq	%rdx, %rax
	movq	%rax, -16(%rbp)
	leaq	-40(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-40(%rbp), %rax
	salq	$2, %rax
	movq	%rax, -8(%rbp)
.L2:
	movq	-40(%rbp), %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -40(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	leaq	5(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	subq	$2, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jg	.L2
	movq	-40(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	dw_loop, .-dw_loop
	.ident	"GCC: (GNU) 15.2.1 20251211 (Red Hat 15.2.1-5)"
	.section	.note.GNU-stack,"",@progbits
