GLOBAL cpuVendor
; GLOBAL enableSSE

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

; enableSSE:
; 	;now enable SSE and the like
; 	mov rax, cr0
; 	and ax, 0xFFFB		;clear coprocessor emulation CR0.EM
; 	or ax, 0x2			;set coprocessor monitoring  CR0.MP
; 	mov cr0, rax
; 	mov rax, cr4
; 	or ax, 3 << 9		;set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
; 	mov cr4, rax
; 	ret
