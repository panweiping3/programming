	.file	"a.c"
	.section	.rodata
.LC0:
	.string	"abcdefg"
	.data
	.align 4
	.type	foo.2149, @object
	.size	foo.2149, 4
foo.2149:
	.long	.LC0
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
	subl	$4, %esp
	movl	foo.2149, %eax
	movl	%eax, (%esp)
	call	puts
	movl	$0, %eax
	addl	$4, %esp
	popl	%ecx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.2.1"
	.section	.note.GNU-stack,"",@progbits
