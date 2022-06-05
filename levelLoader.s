	.file	"levelLoader.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"M\303\251moire insuffisante !\n"
	.text
	.p2align 4
	.type	insertInfo.part.0, @function
insertInfo.part.0:
.LFB68:
	.cfi_startproc
	pushq	%rax
	.cfi_def_cfa_offset 16
	popq	%rax
	.cfi_def_cfa_offset 8
	leaq	.LC0(%rip), %rdi
	movl	$24, %edx
	movl	$1, %esi
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movq	stderr(%rip), %rcx
	call	fwrite@PLT
	movl	$1, %edi
	call	exit@PLT
	.cfi_endproc
.LFE68:
	.size	insertInfo.part.0, .-insertInfo.part.0
	.section	.rodata.str1.1
.LC1:
	.string	"Liste vide!"
.LC2:
	.string	"Contenu de la liste : "
.LC3:
	.string	"%d "
	.text
	.p2align 4
	.globl	listeAffiche
	.type	listeAffiche, @function
listeAffiche:
.LFB59:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	levelsNode(%rip), %rbx
	testq	%rbx, %rbx
	je	.L10
	leaq	.LC2(%rip), %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	leaq	.LC3(%rip), %rbp
	.p2align 4,,10
	.p2align 3
.L7:
	movl	(%rbx), %edx
	movq	%rbp, %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movq	56(%rbx), %rbx
	testq	%rbx, %rbx
	jne	.L7
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movl	$10, %edi
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	putchar@PLT
	.p2align 4,,10
	.p2align 3
.L10:
	.cfi_restore_state
	movl	$1, %edi
	leaq	.LC1(%rip), %rsi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	movl	$10, %edi
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	putchar@PLT
	.cfi_endproc
.LFE59:
	.size	listeAffiche, .-listeAffiche
	.section	.rodata.str1.1
.LC4:
	.string	"r"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC5:
	.string	"Erreur lors de l'ouverture du fichier...\n"
	.section	.rodata.str1.1
.LC6:
	.string	""
.LC7:
	.string	"\r"
.LC8:
	.string	"\n"
.LC9:
	.string	";LEVEL"
.LC10:
	.string	";AUTHOR"
.LC11:
	.string	";COMMENT"
.LC12:
	.string	";SUCCESS"
	.text
	.p2align 4
	.globl	readLevelsFile
	.type	readLevelsFile, @function
readLevelsFile:
.LFB62:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	leaq	.LC4(%rip), %rsi
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	leaq	.LC9(%rip), %r13
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$56, %rsp
	.cfi_def_cfa_offset 112
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	leaq	24(%rsp), %r12
	leaq	32(%rsp), %rbx
	movq	$0, 24(%rsp)
	movq	$0, 32(%rsp)
	call	fopen@PLT
	movq	%rax, %rbp
	testq	%rax, %rax
	je	.L78
	.p2align 4,,10
	.p2align 3
.L12:
	movq	%rbp, %rcx
	movl	$10, %edx
	movq	%r12, %rsi
	movq	%rbx, %rdi
	call	__getdelim@PLT
	cmpl	$-1, %eax
	je	.L79
	movq	32(%rsp), %r15
	movl	$13, %esi
	movq	%r15, %rdi
	call	strchr@PLT
	testq	%rax, %rax
	je	.L13
	leaq	.LC7(%rip), %rsi
	movq	%r15, %rdi
	call	strcspn@PLT
	movb	$0, (%r15,%rax)
.L13:
	movl	$10, %esi
	movq	%r15, %rdi
	call	strchr@PLT
	testq	%rax, %rax
	je	.L14
	leaq	.LC8(%rip), %rsi
	movq	%r15, %rdi
	call	strcspn@PLT
	movb	$0, (%r15,%rax)
.L14:
	movl	$6, %ecx
	movq	%r13, %rsi
	movq	%r15, %rdi
	repz cmpsb
	seta	%al
	sbbb	$0, %al
	testb	%al, %al
	je	.L71
	movl	$7, %ecx
	leaq	.LC10(%rip), %rsi
	movq	%r15, %rdi
	repz cmpsb
	seta	%al
	sbbb	$0, %al
	testb	%al, %al
	je	.L72
	movl	$8, %ecx
	leaq	.LC11(%rip), %rsi
	movq	%r15, %rdi
	repz cmpsb
	seta	%al
	sbbb	$0, %al
	testb	%al, %al
	je	.L73
	movl	$8, %ecx
	leaq	.LC12(%rip), %rsi
	movq	%r15, %rdi
	repz cmpsb
	seta	%al
	sbbb	$0, %al
	testb	%al, %al
	je	.L74
	cmpq	$0, levelsNode(%rip)
	je	.L12
	movq	currentLevel.3804(%rip), %r14
	movl	40(%r14), %eax
	movq	32(%r14), %rdi
	leal	1(%rax), %esi
	salq	$3, %rsi
	call	realloc@PLT
	testq	%rax, %rax
	je	.L77
	movq	%r15, %rdi
	movq	%rax, 8(%rsp)
	call	strlen@PLT
	movl	40(%r14), %edx
	leaq	1(%rax), %rdi
	movl	%edx, (%rsp)
	call	malloc@PLT
	movq	8(%rsp), %rcx
	movq	%rax, %rdi
	movl	(%rsp), %eax
	movq	%rdi, (%rcx,%rax,8)
	testq	%rdi, %rdi
	je	.L77
	movq	%r15, %rsi
	movq	%rcx, 8(%rsp)
	call	strcpy@PLT
	movl	(%rsp), %eax
	movq	8(%rsp), %rcx
	addl	$1, %eax
	movq	%rcx, 32(%r14)
	movl	%eax, 40(%r14)
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L17:
	addq	$1, %r15
.L71:
	testb	$-33, (%r15)
	jne	.L17
	leaq	1(%r15), %rdi
	xorl	%esi, %esi
	movl	$10, %edx
	call	strtol@PLT
	movl	$64, %edi
	movq	%rax, %r14
	call	malloc@PLT
	testq	%rax, %rax
	je	.L77
	movq	levelsNode(%rip), %rdx
	pxor	%xmm0, %xmm0
	movl	%r14d, (%rax)
	movb	$0, 24(%rax)
	movq	$0, 32(%rax)
	movl	$0, 40(%rax)
	movq	$0, 56(%rax)
	movups	%xmm0, 8(%rax)
	testq	%rdx, %rdx
	je	.L80
	.p2align 4,,10
	.p2align 3
.L19:
	movq	%rdx, %rcx
	movq	56(%rdx), %rdx
	testq	%rdx, %rdx
	jne	.L19
	movq	%rax, 56(%rcx)
.L20:
	movq	%rax, currentLevel.3804(%rip)
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L24:
	addq	$1, %r15
.L72:
	testb	$-33, (%r15)
	jne	.L24
	addq	$1, %r15
	movq	currentLevel.3804(%rip), %r14
	movq	%r15, %rdi
	call	strlen@PLT
	leaq	1(%rax), %rdi
	call	malloc@PLT
	movq	%rax, 8(%r14)
	movq	%rax, %rdi
	testq	%rax, %rax
	je	.L29
.L75:
	movq	%r15, %rsi
	call	strcpy@PLT
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L28:
	addq	$1, %r15
.L73:
	testb	$-33, (%r15)
	jne	.L28
	movq	currentLevel.3804(%rip), %rdx
	addq	$1, %r15
	movq	%r15, %rdi
	movq	%rdx, (%rsp)
	call	strlen@PLT
	leaq	1(%rax), %rdi
	call	malloc@PLT
	movq	(%rsp), %rdx
	movq	%rax, %rdi
	movq	%rax, 16(%rdx)
	testq	%rax, %rax
	jne	.L75
.L29:
	call	insertInfo.part.0
	.p2align 4,,10
	.p2align 3
.L32:
	addq	$1, %r15
.L74:
	testb	$-33, (%r15)
	jne	.L32
	movl	$10, %edx
	leaq	1(%r15), %rdi
	xorl	%esi, %esi
	call	strtol@PLT
	movq	currentLevel.3804(%rip), %rdx
	movb	%al, 24(%rdx)
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L79:
	movq	32(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L36
	call	free@PLT
	movq	$0, 32(%rsp)
.L36:
	movq	%rbp, %rdi
	call	fclose@PLT
	movq	40(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L81
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L80:
	.cfi_restore_state
	movq	%rax, levelsNode(%rip)
	jmp	.L20
	.p2align 4,,10
	.p2align 3
.L78:
	movq	stderr(%rip), %rcx
	movl	$41, %edx
	movl	$1, %esi
	leaq	.LC5(%rip), %rdi
	call	fwrite@PLT
	leaq	.LC6(%rip), %rdi
	call	perror@PLT
	xorl	%edi, %edi
	call	exit@PLT
.L77:
	movq	stderr(%rip), %rcx
	movl	$24, %edx
	movl	$1, %esi
	leaq	.LC0(%rip), %rdi
	call	fwrite@PLT
	movl	$1, %edi
	call	exit@PLT
.L81:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE62:
	.size	readLevelsFile, .-readLevelsFile
	.p2align 4
	.globl	determinePlayerCoord
	.type	determinePlayerCoord, @function
determinePlayerCoord:
.LFB67:
	.cfi_startproc
	endbr64
	movl	40(%rdi), %r10d
	movq	32(%rdi), %r8
	xorl	%esi, %esi
.L86:
	movq	(%r8,%rsi,8), %rcx
	movl	%esi, %r9d
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L85:
	movzbl	(%rcx,%rax), %edx
	cmpb	$64, %dl
	je	.L89
	addq	$1, %rax
	testb	%dl, %dl
	jne	.L85
	addq	$1, %rsi
	cmpl	%esi, %r10d
	jnb	.L86
	ret
	.p2align 4,,10
	.p2align 3
.L89:
	movl	%r9d, 44(%rdi)
	movl	%eax, 48(%rdi)
	ret
	.cfi_endproc
.LFE67:
	.size	determinePlayerCoord, .-determinePlayerCoord
	.local	currentLevel.3804
	.comm	currentLevel.3804,8,8
	.globl	levelsNode
	.bss
	.align 8
	.type	levelsNode, @object
	.size	levelsNode, 8
levelsNode:
	.zero	8
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
