	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0	sdk_version 13, 1
	.intel_syntax noprefix
	.globl	_main                           ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	push	r15
	push	r14
	push	r12
	push	rbx
	sub	rsp, 48
	.cfi_offset rbx, -48
	.cfi_offset r12, -40
	.cfi_offset r14, -32
	.cfi_offset r15, -24
	mov	rax, qword ptr [rip + l___const.main.a+32]
	mov	qword ptr [rbp - 48], rax
	movups	xmm0, xmmword ptr [rip + l___const.main.a+16]
	movaps	xmmword ptr [rbp - 64], xmm0
	movups	xmm0, xmmword ptr [rip + l___const.main.a]
	movaps	xmmword ptr [rbp - 80], xmm0
	xor	r8d, r8d
	mov	ecx, 4
	mov	r9d, 2
	mov	r10d, 6
	mov	r11d, 3
	mov	r14d, 9
	mov	r15d, 7
	mov	r12d, 8
	mov	ebx, 1
	mov	edx, 4
	mov	edi, 5
	xor	eax, eax
                                        ## implicit-def: $esi
	.p2align	4, 0x90
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	test	eax, eax
	cmove	esi, r9d
	cmp	eax, 1
	cmove	esi, r10d
	cmp	eax, 2
	cmove	esi, r11d
	cmp	eax, 3
	cmove	esi, r14d
	cmp	eax, 4
	cmove	esi, r15d
	cmp	eax, 5
	cmove	esi, r12d
	cmp	eax, 6
	cmove	esi, ebx
	cmp	eax, 7
	cmove	esi, edx
	cmp	eax, 8
	cmove	esi, r8d
	cmp	eax, 9
	cmove	esi, edi
	cmp	rcx, 40
	je	LBB0_3
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	mov	eax, dword ptr [rbp + rcx - 80]
	add	rcx, 4
	jmp	LBB0_1
LBB0_3:
	mov	rdi, qword ptr [rip + __ZNSt3__14coutE@GOTPCREL]
	call	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi
	xor	eax, eax
	add	rsp, 48
	pop	rbx
	pop	r12
	pop	r14
	pop	r15
	pop	rbp
	ret
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__const
	.p2align	2                               ## @__const.main.a
l___const.main.a:
	.long	0                               ## 0x0
	.long	1                               ## 0x1
	.long	2                               ## 0x2
	.long	3                               ## 0x3
	.long	4                               ## 0x4
	.long	5                               ## 0x5
	.long	6                               ## 0x6
	.long	7                               ## 0x7
	.long	8                               ## 0x8
	.long	9                               ## 0x9

.subsections_via_symbols
