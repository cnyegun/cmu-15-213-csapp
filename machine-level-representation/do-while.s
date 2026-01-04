	.file	"do-while.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%i\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB11:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	$0, %ebx			# i = 0;
.L2:
	movl	$.LC0, %edi    #
	movl	$0, %eax       # x = 0;
	call	printf				 # call printf 
	addl	$1, %ebx			 # i ++;
	cmpl	$99, %ebx			 # compares i to 99
	jle	.L2							 # if i <= 99 goto L2:
	movl	$0, %eax			 # clears %rax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.ident	"GCC: (GNU) 15.2.1 20251211 (Red Hat 15.2.1-5)"
	.section	.note.GNU-stack,"",@progbits
