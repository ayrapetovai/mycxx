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
	je	LBB0_15
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	mov	rax, qword ptr [rbp - 72]
	mov	eax, dword ptr [rax]
	mov	dword ptr [rbp - 84], eax
	mov	eax, dword ptr [rbp - 84]
                                        ## kill: def $rax killed $eax
	mov	qword ptr [rbp - 96], rax       ## 8-byte Spill
	sub	rax, 9
	ja	LBB0_13
## %bb.16:                              ##   in Loop: Header=BB0_1 Depth=1
	mov	rax, qword ptr [rbp - 96]       ## 8-byte Reload
	lea	rcx, [rip + LJTI0_0]
	movsxd	rax, dword ptr [rcx + 4*rax]
	add	rax, rcx
	jmp	rax
LBB0_3:                                 ##   in Loop: Header=BB0_1 Depth=1
	mov	dword ptr [rbp - 52], 2
	jmp	LBB0_13
LBB0_4:                                 ##   in Loop: Header=BB0_1 Depth=1
	mov	dword ptr [rbp - 52], 6
	jmp	LBB0_13
LBB0_5:                                 ##   in Loop: Header=BB0_1 Depth=1
	mov	dword ptr [rbp - 52], 3
	jmp	LBB0_13
LBB0_6:                                 ##   in Loop: Header=BB0_1 Depth=1
	mov	dword ptr [rbp - 52], 9
	jmp	LBB0_13
LBB0_7:                                 ##   in Loop: Header=BB0_1 Depth=1
	mov	dword ptr [rbp - 52], 7
	jmp	LBB0_13
LBB0_8:                                 ##   in Loop: Header=BB0_1 Depth=1
	mov	dword ptr [rbp - 52], 8
	jmp	LBB0_13
LBB0_9:                                 ##   in Loop: Header=BB0_1 Depth=1
	mov	dword ptr [rbp - 52], 1
	jmp	LBB0_13
LBB0_10:                                ##   in Loop: Header=BB0_1 Depth=1
	mov	dword ptr [rbp - 52], 4
	jmp	LBB0_13
LBB0_11:                                ##   in Loop: Header=BB0_1 Depth=1
	mov	dword ptr [rbp - 52], 0
	jmp	LBB0_13
LBB0_12:                                ##   in Loop: Header=BB0_1 Depth=1
	mov	dword ptr [rbp - 52], 5
LBB0_13:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_14
LBB0_14:                                ##   in Loop: Header=BB0_1 Depth=1
	mov	rax, qword ptr [rbp - 72]
	add	rax, 4
	mov	qword ptr [rbp - 72], rax
	jmp	LBB0_1
LBB0_15:
	mov	esi, dword ptr [rbp - 52]
	mov	rdi, qword ptr [rip + __ZNSt3__14coutE@GOTPCREL]
	call	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi
	mov	eax, dword ptr [rbp - 4]
	add	rsp, 96
	pop	rbp
	ret
	.cfi_endproc
	.p2align	2, 0x90
	.data_region jt32
.set L0_0_set_3, LBB0_3-LJTI0_0
.set L0_0_set_4, LBB0_4-LJTI0_0
.set L0_0_set_5, LBB0_5-LJTI0_0
.set L0_0_set_6, LBB0_6-LJTI0_0
.set L0_0_set_7, LBB0_7-LJTI0_0
.set L0_0_set_8, LBB0_8-LJTI0_0
.set L0_0_set_9, LBB0_9-LJTI0_0
.set L0_0_set_10, LBB0_10-LJTI0_0
.set L0_0_set_11, LBB0_11-LJTI0_0
.set L0_0_set_12, LBB0_12-LJTI0_0
LJTI0_0:
	.long	L0_0_set_3
	.long	L0_0_set_4
	.long	L0_0_set_5
	.long	L0_0_set_6
	.long	L0_0_set_7
	.long	L0_0_set_8
	.long	L0_0_set_9
	.long	L0_0_set_10
	.long	L0_0_set_11
	.long	L0_0_set_12
	.end_data_region
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
