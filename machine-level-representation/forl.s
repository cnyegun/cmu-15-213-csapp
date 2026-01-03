	.file	"forl.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	movl	$0, %eax     #store 0 to eax
	movl	$0, %edx		 #store 0 to edx
	jmp	.L2						 #goto L2
	.p2align 4
.L3:
	addl	%eax, %edx	#edx += eax
	addl	$1, %eax		#eax += 1
.L2:									
	cmpl	$4, %eax		#compares eax to 4
	jle	.L3						#if less or equal go to L3
	movl	%edx, %eax  #move edx to return register eax
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 15.2.1 20251211 (Red Hat 15.2.1-5)"
	.section	.note.GNU-stack,"",@progbits
