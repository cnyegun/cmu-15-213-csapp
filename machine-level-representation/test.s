	.file	"test.c"
	.text
	.globl	test
	.type	test, @function
test:
.LFB0:
	.cfi_startproc
	movq	%rdi, %rax
	notq	%rax
	shrq	$63, %rax
	ret
	.cfi_endproc
.LFE0:
	.size	test, .-test
	.ident	"GCC: (GNU) 15.2.1 20251211 (Red Hat 15.2.1-5)"
	.section	.note.GNU-stack,"",@progbits
