	movq %rdi, %rax # x := x
	movq %rdi, %rcx # y := x
	imulq %rdi, %rcx # y := x * x
	leaq (%rdi, %rdi), %rdx # n := 2*x

.L2:
	leaq 1(%rax, %rcx) %rax # x := x + y + 1
	subq $1, %rdx						# n --;
	testq %rdx, %rdx				# comp n to 0
