	.file	"movements.c"
	.text
	.p2align 4
	.globl	move
	.type	move, @function
move:
.LFB34:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rsi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdx, %rbx
	call	getInput@PLT
	cmpl	$2, %eax
	je	.L2
.L132:
	ja	.L3
	testl	%eax, %eax
	je	.L118
	movslq	0(%rbp), %rdx
	movslq	(%r12), %rdi
	movslq	(%rdx), %rcx
	movslq	(%rdi), %rax
	movq	(%rbx,%rcx,8), %r10
	movq	-8(%rbx,%rcx,8), %r11
	movq	%rcx, %rsi
	leaq	0(,%rcx,8), %r8
	addq	%rax, %r10
	addq	%rax, %r11
	cmpb	$79, (%r10)
	je	.L119
	movzbl	(%r11), %r9d
	cmpb	$32, %r9b
	je	.L120
	cmpb	$46, %r9b
	je	.L121
	cmpb	$35, %r9b
	je	.L1
	movq	8(%rbx,%r8), %r9
	movq	-16(%rbx,%r8), %rcx
	cmpb	$36, (%r9,%rax)
	movzbl	(%rcx,%rax), %ecx
	je	.L122
.L28:
	cmpb	$32, %cl
	je	.L123
.L29:
	cmpb	$46, %cl
	je	.L124
.L30:
	subl	$1, %esi
	movl	%esi, (%rdx)
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L3:
	.cfi_restore_state
	cmpl	$3, %eax
	jne	.L125
	movslq	0(%rbp), %r9
	movslq	(%r12), %rax
	movslq	(%r9), %rdx
	movslq	(%rax), %rcx
	movq	(%rbx,%rdx,8), %rdi
	movslq	4(%rax), %rdx
	movq	%rcx, %rsi
	addq	%rdi, %rcx
	addq	%rdi, %rdx
	cmpb	$79, (%rcx)
	movzbl	(%rdx), %r8d
	je	.L126
	cmpb	$32, %r8b
	je	.L127
	cmpb	$46, %r8b
	je	.L128
	cmpb	$35, %r8b
	je	.L1
	movslq	8(%rax), %rdx
	movzbl	(%rdi,%rdx), %edx
	cmpb	$36, %r8b
	je	.L129
.L50:
	cmpb	$32, %dl
	je	.L130
.L51:
	cmpb	$46, %dl
	je	.L131
.L52:
	addl	$1, %esi
	movl	%esi, (%rax)
.L1:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L125:
	.cfi_restore_state
	movslq	(%r12), %r12
	movslq	0(%rbp), %rbp
	call	getInput@PLT
	cmpl	$2, %eax
	jne	.L132
.L2:
	movslq	0(%rbp), %r9
	movslq	(%r12), %rax
	movslq	(%r9), %rdx
	movslq	(%rax), %rcx
	movq	(%rbx,%rdx,8), %rdi
	movslq	-4(%rax), %rdx
	movq	%rcx, %rsi
	addq	%rdi, %rcx
	addq	%rdi, %rdx
	cmpb	$79, (%rcx)
	movzbl	(%rdx), %r8d
	je	.L133
	cmpb	$32, %r8b
	je	.L134
	cmpb	$46, %r8b
	je	.L135
	cmpb	$35, %r8b
	je	.L1
	movslq	-8(%rax), %rdx
	movzbl	(%rdi,%rdx), %edx
	cmpb	$36, %r8b
	je	.L136
.L39:
	cmpb	$32, %dl
	je	.L137
.L40:
	cmpb	$46, %dl
	je	.L138
.L41:
	subl	$1, %esi
	movl	%esi, (%rax)
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L118:
	.cfi_restore_state
	movslq	0(%rbp), %rax
	movslq	(%r12), %r11
	movslq	(%rax), %rdx
	movslq	(%r11), %rcx
	movq	(%rbx,%rdx,8), %r9
	movq	8(%rbx,%rdx,8), %r8
	movq	%rdx, %rdi
	leaq	0(,%rdx,8), %r10
	addq	%rcx, %r9
	addq	%rcx, %r8
	cmpb	$79, (%r9)
	movzbl	(%r8), %esi
	je	.L139
	cmpb	$32, %sil
	je	.L140
	cmpb	$46, %sil
	je	.L141
	cmpb	$35, %sil
	je	.L1
	movq	16(%rbx,%r10), %r8
	movzbl	(%r8,%rcx), %r8d
	cmpb	$36, %sil
	je	.L142
.L17:
	cmpb	$32, %r8b
	je	.L143
.L18:
	cmpb	$46, %r8b
	je	.L144
.L19:
	addl	$1, %edi
	movl	%edi, (%rax)
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L133:
	.cfi_restore_state
	cmpb	$32, %r8b
	je	.L145
	cmpb	$46, %r8b
	je	.L146
	cmpb	$35, %r8b
	je	.L1
	movslq	-8(%rax), %rdx
	movzbl	(%rdi,%rdx), %edx
	cmpb	$36, %r8b
	je	.L147
.L34:
	cmpb	$32, %dl
	jne	.L35
	movb	$46, (%rcx)
	movslq	(%r9), %rcx
	movslq	-4(%rax), %rdx
	movq	(%rbx,%rcx,8), %rcx
	movb	$64, (%rcx,%rdx)
	movslq	(%r9), %rcx
	movslq	-8(%rax), %rdx
	movq	(%rbx,%rcx,8), %rcx
	movb	$36, (%rcx,%rdx)
	movslq	(%r9), %rdx
	movslq	(%rax), %rsi
	movq	(%rbx,%rdx,8), %rdi
	movslq	-8(%rax), %rdx
	movzbl	(%rdi,%rdx), %edx
.L35:
	cmpb	$46, %dl
	jne	.L41
	movb	$46, (%rdi,%rsi)
.L115:
	movslq	(%r9), %rcx
	movslq	-4(%rax), %rdx
	movq	(%rbx,%rcx,8), %rcx
	movb	$64, (%rcx,%rdx)
	movslq	(%r9), %rcx
	movslq	-8(%rax), %rdx
	movq	(%rbx,%rcx,8), %rcx
	movb	$81, (%rcx,%rdx)
	movl	(%rax), %esi
	jmp	.L41
	.p2align 4,,10
	.p2align 3
.L126:
	cmpb	$32, %r8b
	je	.L148
	cmpb	$46, %r8b
	je	.L149
	cmpb	$35, %r8b
	je	.L1
	movslq	8(%rax), %rdx
	movzbl	(%rdi,%rdx), %edx
	cmpb	$36, %r8b
	je	.L150
.L45:
	cmpb	$32, %dl
	jne	.L46
	movb	$46, (%rcx)
	movslq	(%r9), %rcx
	movslq	4(%rax), %rdx
	movq	(%rbx,%rcx,8), %rcx
	movb	$64, (%rcx,%rdx)
	movslq	(%r9), %rcx
	movslq	8(%rax), %rdx
	movq	(%rbx,%rcx,8), %rcx
	movb	$36, (%rcx,%rdx)
	movslq	(%r9), %rdx
	movslq	(%rax), %rsi
	movq	(%rbx,%rdx,8), %rdi
	movslq	8(%rax), %rdx
	movzbl	(%rdi,%rdx), %edx
.L46:
	cmpb	$46, %dl
	jne	.L52
	movb	$46, (%rdi,%rsi)
.L116:
	movslq	(%r9), %rcx
	movslq	4(%rax), %rdx
	movq	(%rbx,%rcx,8), %rcx
	movb	$64, (%rcx,%rdx)
	movslq	(%r9), %rcx
	movslq	8(%rax), %rdx
	movq	(%rbx,%rcx,8), %rcx
	movb	$81, (%rcx,%rdx)
	movl	(%rax), %esi
	jmp	.L52
	.p2align 4,,10
	.p2align 3
.L119:
	movq	8(%rbx,%r8), %r9
	cmpb	$32, (%r9,%rax)
	je	.L151
	movzbl	(%r11), %r9d
	cmpb	$46, %r9b
	je	.L152
	cmpb	$35, %r9b
	je	.L1
	movq	-16(%rbx,%r8), %rcx
	movzbl	(%rcx,%rax), %ecx
	cmpb	$36, %r9b
	je	.L153
.L23:
	cmpb	$32, %cl
	jne	.L24
	movb	$46, (%r10)
	movslq	(%rdx), %rcx
	movslq	(%rdi), %rax
	movq	-8(%rbx,%rcx,8), %rcx
	movb	$64, (%rcx,%rax)
	movslq	(%rdx), %rcx
	movslq	(%rdi), %rax
	movq	-16(%rbx,%rcx,8), %rcx
	movb	$36, (%rcx,%rax)
	movslq	(%rdx), %r8
	movslq	(%rdi), %rax
	movq	%r8, %rsi
	salq	$3, %r8
	movq	-16(%rbx,%r8), %rcx
	movzbl	(%rcx,%rax), %ecx
.L24:
	cmpb	$46, %cl
	jne	.L30
	movq	(%rbx,%r8), %rcx
	movb	$46, (%rcx,%rax)
.L114:
	movslq	(%rdx), %rcx
	movslq	(%rdi), %rax
	movq	-8(%rbx,%rcx,8), %rcx
	movb	$64, (%rcx,%rax)
	movslq	(%rdx), %rcx
	movslq	(%rdi), %rax
	movq	-16(%rbx,%rcx,8), %rcx
	movb	$81, (%rcx,%rax)
	movl	(%rdx), %esi
	jmp	.L30
	.p2align 4,,10
	.p2align 3
.L139:
	cmpb	$32, %sil
	je	.L154
	cmpb	$46, %sil
	je	.L155
	cmpb	$35, %sil
	je	.L1
	movq	16(%rbx,%r10), %r8
	movzbl	(%r8,%rcx), %r8d
	cmpb	$36, %sil
	je	.L156
.L12:
	cmpb	$32, %r8b
	jne	.L13
	movb	$46, (%r9)
	movslq	(%rax), %rcx
	movslq	(%r11), %rdx
	movq	8(%rbx,%rcx,8), %rcx
	movb	$64, (%rcx,%rdx)
	movslq	(%rax), %rcx
	movslq	(%r11), %rdx
	movq	16(%rbx,%rcx,8), %rcx
	movb	$36, (%rcx,%rdx)
	movslq	(%rax), %rdx
	movslq	(%r11), %rcx
	movq	16(%rbx,%rdx,8), %rsi
	movq	%rdx, %rdi
	movzbl	(%rsi,%rcx), %r8d
.L13:
	cmpb	$46, %r8b
	jne	.L19
	movq	(%rbx,%rdx,8), %rdx
	movb	$46, (%rdx,%rcx)
.L113:
	movslq	(%rax), %rcx
	movslq	(%r11), %rdx
	movq	8(%rbx,%rcx,8), %rcx
	movb	$64, (%rcx,%rdx)
	movslq	(%rax), %rcx
	movslq	(%r11), %rdx
	movq	16(%rbx,%rcx,8), %rcx
	movb	$81, (%rcx,%rdx)
	movl	(%rax), %edi
	jmp	.L19
	.p2align 4,,10
	.p2align 3
.L130:
	movb	$32, (%rcx)
	movslq	(%r9), %rcx
	movslq	4(%rax), %rdx
	movq	(%rbx,%rcx,8), %rcx
	movb	$64, (%rcx,%rdx)
	movslq	(%r9), %rcx
	movslq	8(%rax), %rdx
	movq	(%rbx,%rcx,8), %rcx
	movb	$36, (%rcx,%rdx)
	movslq	(%r9), %rdx
	movslq	(%rax), %rsi
	movq	(%rbx,%rdx,8), %rdi
	movslq	8(%rax), %rdx
	movzbl	(%rdi,%rdx), %edx
	jmp	.L51
	.p2align 4,,10
	.p2align 3
.L123:
	movb	$32, (%r10)
	movslq	(%rdx), %rcx
	movslq	(%rdi), %rax
	movq	-8(%rbx,%rcx,8), %rcx
	movb	$64, (%rcx,%rax)
	movslq	(%rdx), %rcx
	movslq	(%rdi), %rax
	movq	-16(%rbx,%rcx,8), %rcx
	movb	$36, (%rcx,%rax)
	movslq	(%rdx), %r8
	movslq	(%rdi), %rax
	movq	%r8, %rsi
	salq	$3, %r8
	movq	-16(%rbx,%r8), %rcx
	movzbl	(%rcx,%rax), %ecx
	jmp	.L29
	.p2align 4,,10
	.p2align 3
.L143:
	movb	$32, (%r9)
	movslq	(%rax), %rcx
	movslq	(%r11), %rdx
	movq	8(%rbx,%rcx,8), %rcx
	movb	$64, (%rcx,%rdx)
	movslq	(%rax), %rcx
	movslq	(%r11), %rdx
	movq	16(%rbx,%rcx,8), %rcx
	movb	$36, (%rcx,%rdx)
	movslq	(%rax), %rdx
	movslq	(%r11), %rcx
	movq	16(%rbx,%rdx,8), %rsi
	movq	%rdx, %rdi
	movzbl	(%rsi,%rcx), %r8d
	jmp	.L18
	.p2align 4,,10
	.p2align 3
.L137:
	movb	$32, (%rcx)
	movslq	(%r9), %rcx
	movslq	-4(%rax), %rdx
	movq	(%rbx,%rcx,8), %rcx
	movb	$64, (%rcx,%rdx)
	movslq	(%r9), %rcx
	movslq	-8(%rax), %rdx
	movq	(%rbx,%rcx,8), %rcx
	movb	$36, (%rcx,%rdx)
	movslq	(%r9), %rdx
	movslq	(%rax), %rsi
	movq	(%rbx,%rdx,8), %rdi
	movslq	-8(%rax), %rdx
	movzbl	(%rdi,%rdx), %edx
	jmp	.L40
	.p2align 4,,10
	.p2align 3
.L124:
	movq	(%rbx,%r8), %rcx
	movb	$32, (%rcx,%rax)
	jmp	.L114
	.p2align 4,,10
	.p2align 3
.L138:
	movb	$32, (%rdi,%rsi)
	jmp	.L115
	.p2align 4,,10
	.p2align 3
.L144:
	movq	(%rbx,%rdx,8), %rdx
	movb	$32, (%rdx,%rcx)
	jmp	.L113
	.p2align 4,,10
	.p2align 3
.L131:
	movb	$32, (%rdi,%rsi)
	jmp	.L116
	.p2align 4,,10
	.p2align 3
.L134:
	movb	$64, (%rdx)
.L112:
	movslq	(%r9), %rcx
	movslq	(%rax), %rdx
	movq	(%rbx,%rcx,8), %rcx
	movb	$32, (%rcx,%rdx)
	subl	$1, (%rax)
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L127:
	movb	$64, (%rdx)
.L107:
	movslq	(%r9), %rcx
	movslq	(%rax), %rdx
	movq	(%rbx,%rcx,8), %rcx
	movb	$32, (%rcx,%rdx)
	addl	$1, (%rax)
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L140:
	movb	$64, (%r8)
.L106:
	movslq	(%rax), %rcx
	movslq	(%r11), %rdx
	movq	(%rbx,%rcx,8), %rcx
	movb	$32, (%rcx,%rdx)
	addl	$1, (%rax)
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L120:
	movb	$64, (%r11)
.L109:
	movslq	(%rdx), %rcx
	movslq	(%rdi), %rax
	movq	(%rbx,%rcx,8), %rcx
	movb	$32, (%rcx,%rax)
	subl	$1, (%rdx)
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L129:
	cmpb	$35, %dl
	jne	.L50
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L122:
	cmpb	$35, %cl
	jne	.L28
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L142:
	cmpb	$35, %r8b
	jne	.L17
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L136:
	cmpb	$35, %dl
	jne	.L39
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L141:
	movb	$79, (%r8)
	jmp	.L106
	.p2align 4,,10
	.p2align 3
.L121:
	movb	$79, (%r11)
	jmp	.L109
	.p2align 4,,10
	.p2align 3
.L135:
	movb	$79, (%rdx)
	jmp	.L112
	.p2align 4,,10
	.p2align 3
.L128:
	movb	$79, (%rdx)
	jmp	.L107
	.p2align 4,,10
	.p2align 3
.L148:
	movb	$64, (%rdx)
.L110:
	movslq	(%r9), %rcx
	movslq	(%rax), %rdx
	movq	(%rbx,%rcx,8), %rcx
	movb	$46, (%rcx,%rdx)
	addl	$1, (%rax)
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L145:
	movb	$64, (%rdx)
.L111:
	movslq	(%r9), %rcx
	movslq	(%rax), %rdx
	movq	(%rbx,%rcx,8), %rcx
	movb	$46, (%rcx,%rdx)
	subl	$1, (%rax)
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L151:
	movb	$64, (%r11)
.L108:
	movslq	(%rdx), %rcx
	movslq	(%rdi), %rax
	movq	(%rbx,%rcx,8), %rcx
	movb	$46, (%rcx,%rax)
	subl	$1, (%rdx)
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L154:
	movb	$64, (%r8)
.L105:
	movslq	(%rax), %rcx
	movslq	(%r11), %rdx
	movq	(%rbx,%rcx,8), %rcx
	movb	$46, (%rcx,%rdx)
	addl	$1, (%rax)
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L153:
	cmpb	$35, %cl
	jne	.L23
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L156:
	cmpb	$35, %r8b
	jne	.L12
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L147:
	cmpb	$35, %dl
	jne	.L34
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L150:
	cmpb	$35, %dl
	jne	.L45
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L146:
	movb	$79, (%rdx)
	jmp	.L111
	.p2align 4,,10
	.p2align 3
.L149:
	movb	$79, (%rdx)
	jmp	.L110
	.p2align 4,,10
	.p2align 3
.L152:
	movb	$79, (%r11)
	jmp	.L108
	.p2align 4,,10
	.p2align 3
.L155:
	movb	$79, (%r8)
	jmp	.L105
	.cfi_endproc
.LFE34:
	.size	move, .-move
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
