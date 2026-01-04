	.file	"cond.c"
	.text
	.globl	cond
	.type	cond, @function
cond:
.LFB0:
	.cfi_startproc
	testw	%di, %di
	je	.L1
	cmpw	%di, (%rsi)
	jle	.L1
	movw	%di, (%rsi)
.L2:
.L1:
	ret
	.cfi_endproc
.LFE0:
	.size	cond, .-cond
	.globl	absdiff_se
	.type	absdiff_se, @function
absdiff_se:
.LFB1:
	.cfi_startproc
	cmpl	%esi, %edi
	jle	.L4
	movl	%edi, %eax
	subl	%esi, %eax
	ret
.L4:
	movl	%esi, %eax
	subl	%edi, %eax
.L5:
	ret
	.cfi_endproc
.LFE1:
	.size	absdiff_se, .-absdiff_se
	.globl	test
	.type	test, @function
test:
.LFB2:
	.cfi_startproc
	leal	(%rdx,%rsi), %ecx
	subl	%edi, %ecx
	movl	%ecx, %eax
	cmpw	$5, %cx
	jle	.L7
	cmpw	$2, %si
	jle	.L8
	movswl	%di, %eax
	movswl	%dx, %ecx
	cltd
	idivl	%ecx
	ret
.L8:
	movswl	%di, %eax
	movswl	%si, %esi
	cltd
	idivl	%esi
	ret
.L7:
	cmpw	$2, %si
	jg	.L6
	movswl	%dx, %eax
	movswl	%si, %esi
	cltd
	idivl	%esi
.L6:
	ret
	.cfi_endproc
.LFE2:
	.size	test, .-test
	.ident	"GCC: (GNU) 15.2.1 20251211 (Red Hat 15.2.1-5)"
	.section	.note.GNU-stack,"",@progbits
