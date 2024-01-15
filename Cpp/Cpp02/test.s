	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15, 6
	.intel_syntax noprefix
	.section	__TEXT,__literal4,4byte_literals
	.p2align	2               ## -- Begin function main
LCPI0_0:
	.long	1092616192              ## float 10
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	sub	rsp, 16
	mov	rdi, qword ptr [rip + __ZNSt3__13cinE@GOTPCREL]
	lea	rsi, [rbp - 4]
	call	__ZNSt3__113basic_istreamIcNS_11char_traitsIcEEErsERi
	cvtsi2ss	xmm0, dword ptr [rbp - 4]
	divss	xmm0, dword ptr [rip + LCPI0_0]
	cvttss2si	esi, xmm0
	mov	rdi, qword ptr [rip + __ZNSt3__14coutE@GOTPCREL]
	call	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi
	xor	eax, eax
	add	rsp, 16
	pop	rbp
	ret
	.cfi_endproc
                                        ## -- End function
.subsections_via_symbols
