	.file	"char.c"
	.section	.rodata
.LC0:
	.string	"abc123"
	.text
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ecx
	subl	$20, %esp
	movl	$.LC0, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, (%esp)
	call	puts
	movl	$0, %eax
	addl	$20, %esp
	popl	%ecx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.2.1"
	.section	.note.GNU-stack,"",@progbits
