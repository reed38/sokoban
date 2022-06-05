	.file	"graphics.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"tcgetattr"
.LC1:
	.string	"tcsetattr"
	.text
	.p2align 4
	.globl	configureTerminal
	.type	configureTerminal, @function
configureTerminal:
.LFB61:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	xorl	%edi, %edi
	subq	$96, %rsp
	.cfi_def_cfa_offset 112
	movq	%fs:40, %rax
	movq	%rax, 88(%rsp)
	xorl	%eax, %eax
	leaq	16(%rsp), %r12
	movq	%r12, %rsi
	call	tcgetattr@PLT
	cmpl	$-1, %eax
	je	.L8
	movl	$256, %eax
	movq	%r12, %rdx
	xorl	%esi, %esi
	xorl	%edi, %edi
	andl	$-11, 28(%rsp)
	movw	%ax, 38(%rsp)
	call	tcsetattr@PLT
	movl	%eax, %r8d
	movl	$1, %eax
	cmpl	$-1, %r8d
	je	.L9
.L1:
	movq	88(%rsp), %rcx
	xorq	%fs:40, %rcx
	jne	.L10
	addq	$96, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L8:
	.cfi_restore_state
	leaq	.LC0(%rip), %rdi
	movl	%eax, 12(%rsp)
	call	perror@PLT
	movl	12(%rsp), %eax
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L9:
	leaq	.LC1(%rip), %rdi
	call	perror@PLT
	xorl	%eax, %eax
	jmp	.L1
.L10:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE61:
	.size	configureTerminal, .-configureTerminal
	.section	.rodata.str1.1
.LC2:
	.string	"clear"
	.text
	.p2align 4
	.globl	terminalReset
	.type	terminalReset, @function
terminalReset:
.LFB62:
	.cfi_startproc
	endbr64
	leaq	.LC2(%rip), %rdi
	jmp	system@PLT
	.cfi_endproc
.LFE62:
	.size	terminalReset, .-terminalReset
	.p2align 4
	.globl	terminalRefresh
	.type	terminalRefresh, @function
terminalRefresh:
.LFB63:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movl	%esi, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	leaq	.LC2(%rip), %rdi
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	call	system@PLT
	testl	%ebp, %ebp
	jle	.L12
	leal	-1(%rbp), %eax
	leaq	8(%rbx,%rax,8), %rbp
	.p2align 4,,10
	.p2align 3
.L14:
	movq	(%rbx), %rdi
	addq	$8, %rbx
	call	puts@PLT
	cmpq	%rbp, %rbx
	jne	.L14
.L12:
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE63:
	.size	terminalRefresh, .-terminalRefresh
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
