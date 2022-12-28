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
	sub	rsp, 96
	mov	dword ptr [rbp - 4], 0
	lea	rdi, [rbp - 48]
	lea	rsi, [rip + l___const.main.a]
	mov	edx, 40
	call	_memcpy
	lea	rax, [rbp - 48]
	mov	qword ptr [rbp - 64], rax
	mov	rdi, qword ptr [rbp - 64]
	call	__ZNSt3__15arrayIiLm10EE5beginEv
	mov	qword ptr [rbp - 72], rax
	mov	rdi, qword ptr [rbp - 64]
	call	__ZNSt3__15arrayIiLm10EE3endEv
	mov	qword ptr [rbp - 80], rax
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	mov	rax, qword ptr [rbp - 72]
	cmp	rax, qword ptr [rbp - 80]
	je	LBB0_33
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	mov	rax, qword ptr [rbp - 72]
	mov	eax, dword ptr [rax]
	mov	dword ptr [rbp - 84], eax
	cmp	dword ptr [rbp - 84], 0
	jne	LBB0_4
## %bb.3:                               ##   in Loop: Header=BB0_1 Depth=1
	mov	dword ptr [rbp - 52], 2
	jmp	LBB0_31
LBB0_4:                                 ##   in Loop: Header=BB0_1 Depth=1
	cmp	dword ptr [rbp - 84], 1
	jne	LBB0_6
## %bb.5:                               ##   in Loop: Header=BB0_1 Depth=1
	mov	dword ptr [rbp - 52], 6
	jmp	LBB0_30
LBB0_6:                                 ##   in Loop: Header=BB0_1 Depth=1
	cmp	dword ptr [rbp - 84], 2
	jne	LBB0_8
## %bb.7:                               ##   in Loop: Header=BB0_1 Depth=1
	mov	dword ptr [rbp - 52], 3
	jmp	LBB0_29
LBB0_8:                                 ##   in Loop: Header=BB0_1 Depth=1
	cmp	dword ptr [rbp - 84], 3
	jne	LBB0_10
## %bb.9:                               ##   in Loop: Header=BB0_1 Depth=1
	mov	dword ptr [rbp - 52], 9
	jmp	LBB0_28
LBB0_10:                                ##   in Loop: Header=BB0_1 Depth=1
	cmp	dword ptr [rbp - 84], 4
	jne	LBB0_12
## %bb.11:                              ##   in Loop: Header=BB0_1 Depth=1
	mov	dword ptr [rbp - 52], 7
	jmp	LBB0_27
LBB0_12:                                ##   in Loop: Header=BB0_1 Depth=1
	cmp	dword ptr [rbp - 84], 5
	jne	LBB0_14
## %bb.13:                              ##   in Loop: Header=BB0_1 Depth=1
	mov	dword ptr [rbp - 52], 8
	jmp	LBB0_26
LBB0_14:                                ##   in Loop: Header=BB0_1 Depth=1
	cmp	dword ptr [rbp - 84], 6
	jne	LBB0_16
## %bb.15:                              ##   in Loop: Header=BB0_1 Depth=1
	mov	dword ptr [rbp - 52], 1
	jmp	LBB0_25
LBB0_16:                                ##   in Loop: Header=BB0_1 Depth=1
	cmp	dword ptr [rbp - 84], 7
	jne	LBB0_18
## %bb.17:                              ##   in Loop: Header=BB0_1 Depth=1
	mov	dword ptr [rbp - 52], 4
	jmp	LBB0_24
LBB0_18:                                ##   in Loop: Header=BB0_1 Depth=1
	cmp	dword ptr [rbp - 84], 8
	jne	LBB0_20
## %bb.19:                              ##   in Loop: Header=BB0_1 Depth=1
	mov	dword ptr [rbp - 52], 0
	jmp	LBB0_23
LBB0_20:                                ##   in Loop: Header=BB0_1 Depth=1
	cmp	dword ptr [rbp - 84], 9
	jne	LBB0_22
## %bb.21:                              ##   in Loop: Header=BB0_1 Depth=1
	mov	dword ptr [rbp - 52], 5
LBB0_22:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_23
LBB0_23:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_24
LBB0_24:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_25
LBB0_25:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_26
LBB0_26:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_27
LBB0_27:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_28
LBB0_28:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_29
LBB0_29:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_30
LBB0_30:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_31
LBB0_31:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_32
LBB0_32:                                ##   in Loop: Header=BB0_1 Depth=1
	mov	rax, qword ptr [rbp - 72]
	add	rax, 4
	mov	qword ptr [rbp - 72], rax
	jmp	LBB0_1
LBB0_33:
	mov	esi, dword ptr [rbp - 52]
	mov	rdi, qword ptr [rip + __ZNSt3__14coutE@GOTPCREL]
	call	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi
	mov	eax, dword ptr [rbp - 4]
	add	rsp, 96
	pop	rbp
	ret
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function _ZNSt3__15arrayIiLm10EE5beginEv
__ZNSt3__15arrayIiLm10EE5beginEv:       ## @_ZNSt3__15arrayIiLm10EE5beginEv
	.cfi_startproc
## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	sub	rsp, 16
	mov	qword ptr [rbp - 8], rdi
	mov	rdi, qword ptr [rbp - 8]
	call	__ZNSt3__15arrayIiLm10EE4dataEv
	add	rsp, 16
	pop	rbp
	ret
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function _ZNSt3__15arrayIiLm10EE3endEv
__ZNSt3__15arrayIiLm10EE3endEv:         ## @_ZNSt3__15arrayIiLm10EE3endEv
	.cfi_startproc
## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	sub	rsp, 16
	mov	qword ptr [rbp - 8], rdi
	mov	rdi, qword ptr [rbp - 8]
	call	__ZNSt3__15arrayIiLm10EE4dataEv
	add	rax, 40
	add	rsp, 16
	pop	rbp
	ret
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function _ZNSt3__15arrayIiLm10EE4dataEv
__ZNSt3__15arrayIiLm10EE4dataEv:        ## @_ZNSt3__15arrayIiLm10EE4dataEv
	.cfi_startproc
## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	mov	qword ptr [rbp - 8], rdi
	mov	rax, qword ptr [rbp - 8]
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
