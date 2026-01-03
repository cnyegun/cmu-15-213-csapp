	.file	"whl.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	movl	$0, %eax #store 0 to eax
	jmp	.L2
	.p2align 3
.L3:
	addl	$1, %eax	# %eax += 1
.L2:
	cmpl	$2, %eax #compares %eax and 2
	jle	.L3				 #if less or equal than 2 -> goto L3
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 15.2.1 20251211 (Red Hat 15.2.1-5)"
	.section	.note.GNU-stack,"",@progbits
