GLOBAL saveState

section .text


%macro saveRegister 1
  mov [rdi], %1
  add rdi, 8
%endmacro

saveState:
  saveRegister rax
	saveRegister rbx
	saveRegister rcx
	saveRegister rdx
	saveRegister rbp
	saveRegister rdi
	saveRegister rsi
	saveRegister r8
	saveRegister r9
	saveRegister r10
	saveRegister r11
	saveRegister r12
	saveRegister r13
	saveRegister r14
	saveRegister r15
  ret