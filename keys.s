	.file	"keys.c"
	.text
	.p2align 4
	.globl	litClavier
	.type	litClavier, @function
litClavier:
.LFB34:
	.cfi_startproc
	endbr64
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movl	$3, %edx
	xorl	%edi, %edi
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	leaq	14(%rsp), %rsi
	call	read@PLT
	xorl	%r8d, %r8d
	cmpl	$-1, %eax
	je	.L1
	movzbl	14(%rsp), %edx
	cmpb	$27, %dl
	je	.L3
	movsbl	%dl, %r8d
.L1:
	movq	24(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L10
	movl	%r8d, %eax
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L3:
	.cfi_restore_state
	cmpl	$3, %eax
	jne	.L1
	cmpb	$91, 15(%rsp)
	jne	.L1
	movsbl	16(%rsp), %r8d
	subl	$64, %r8d
	jmp	.L1
.L10:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE34:
	.size	litClavier, .-litClavier
	.p2align 4
	.globl	getInput
	.type	getInput, @function
getInput:
.LFB35:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$32, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	leaq	14(%rsp), %rbx
.L12:
	movl	$3, %edx
	movq	%rbx, %rsi
	xorl	%edi, %edi
	call	read@PLT
	movq	%rax, %rdx
	cmpl	$-1, %eax
	je	.L12
	movsbl	14(%rsp), %eax
	cmpb	$27, %al
	je	.L27
.L16:
	cmpl	$4, %eax
	je	.L21
	jg	.L19
	cmpl	$2, %eax
	je	.L22
	cmpl	$3, %eax
	jne	.L28
	xorl	%eax, %eax
.L11:
	movq	24(%rsp), %rcx
	xorq	%fs:40, %rcx
	jne	.L29
	addq	$32, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L19:
	.cfi_restore_state
	cmpl	$98, %eax
	je	.L25
	cmpl	$114, %eax
	jne	.L12
	movl	$4, %eax
	jmp	.L11
.L28:
	cmpl	$1, %eax
	jne	.L12
	movl	$3, %eax
	jmp	.L11
	.p2align 4,,10
	.p2align 3
.L25:
	movl	$5, %eax
	jmp	.L11
	.p2align 4,,10
	.p2align 3
.L22:
	movl	$2, %eax
	jmp	.L11
	.p2align 4,,10
	.p2align 3
.L27:
	cmpl	$3, %edx
	jne	.L12
	cmpb	$91, 15(%rsp)
	jne	.L12
	movsbl	16(%rsp), %eax
	subl	$64, %eax
	jmp	.L16
	.p2align 4,,10
	.p2align 3
.L21:
	movl	$1, %eax
	jmp	.L11
.L29:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE35:
	.size	getInput, .-getInput
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
