	.file	"fact.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d\n"
.LC1:
	.string	"OVERFLOW!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movl	$1, %ebp
	movl	$1, %ebx
	jmp	.L2
	.p2align 4
.L4:
	imull	%ebx, %ebp
	addl	$1, %ebx
.L2:
	cmpl	$14, %ebx
	jg	.L6
	testl	%ebx, %ebx
	je	.L4
	movl	$2147483647, %eax
	movl	$0, %edx
	idivl	%ebx
	cmpl	%ebp, %eax
	jge	.L4
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	jmp	.L4
.L6:
	movl	%ebp, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	%ebp, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.ident	"GCC: (GNU) 15.2.1 20251211 (Red Hat 15.2.1-5)"
	.section	.note.GNU-stack,"",@progbits
