	.file	"cmove.c"
	.text
	.p2align 4
	.globl	absdiff
	.type	absdiff, @function
absdiff:
.LFB0:
	.cfi_startproc
	movq	%rsi, %rdx    # rdx = x;
	movq	%rdi, %rax		# rax = x;
	subq	%rdi, %rdx		# rdx = x - y;
	subq	%rsi, %rax		# rax = y - x;
	cmpq	%rsi, %rdi		# if x > y
	cmovl	%rdx, %rax		# 	rax = rdx
	ret									# return rax
	.cfi_endproc
.LFE0:
	.size	absdiff, .-absdiff
	.p2align 4
	.globl	cmovediff
	.type	cmovediff, @function
cmovediff:
.LFB1:
	.cfi_startproc
	movq	%rsi, %rdx
	movq	%rdi, %rax
	subq	%rdi, %rdx
	subq	%rsi, %rax
	cmpq	%rdi, %rsi
	cmovg	%rdx, %rax
	ret
	.cfi_endproc
.LFE1:
	.size	cmovediff, .-cmovediff
	.ident	"GCC: (GNU) 15.2.1 20251211 (Red Hat 15.2.1-5)"
	.section	.note.GNU-stack,"",@progbits
