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
	mov	rdi, qword ptr [rip + __ZNSt3__14coutE@GOTPCREL]
	mov	esi, 5
	call	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi
	xor	eax, eax
	pop	rbp
	ret
	.cfi_endproc
                                        ## -- End function
.subsections_via_symbols
