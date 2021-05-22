
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
EXTERN ncPrintReg
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler

GLOBAL _exception0Handler

EXTERN irqDispatcher
EXTERN exceptionDispatcher

SECTION .text


%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState
	cli ; linea agregada para que no se puede interrumpir las interrupciones de hardware. Para atender de a una interrupcion a la vez.

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	sti ; linea agregada para deshabilitar que no se pueda interrumpir las interrupciones de hardware
	popState
	iretq
%endmacro



%macro exceptionHandler 1
	pushState
	mov rdi, %1 ; pasaje de parametro
	call exceptionDispatcher
	call dumpRegs
	call haltcpu ; cortamos la ejecucion del sistema operativo. En este punto, hay que reiniciarlo.
	; popState
	; iretq
%endmacro

dumpRegs:
	
	push rdi
	push rsi

	push rdi
	lea rdi, [regsNames+4*1]
	call ncPrintReg
	pop rdi
	
	mov rsi, rdi
	lea rdi, [regsNames]
	call ncPrintReg

	mov rsi, rax
	lea rdi, [regsNames+4*2]
	call ncPrintReg

	mov rsi, rbx
	lea rdi, [regsNames+4*3]
	call ncPrintReg
	
	mov rsi, rcx
	lea rdi, [regsNames+4*4]
	call ncPrintReg

	mov rsi, rdx
	lea rdi, [regsNames+4*5]
	call ncPrintReg

	mov rsi, r8
	lea rdi, [regsNames+4*6]
	call ncPrintReg

	mov rsi, r9
	lea rdi, [regsNames+4*7]
	call ncPrintReg
	
	mov rsi, r10
	lea rdi, [regsNames+4*8]
	call ncPrintReg
	
	mov rsi, r11
	lea rdi, [regsNames+4*9]
	call ncPrintReg

	mov rsi, r12
	lea rdi, [regsNames+4*10]
	call ncPrintReg

	mov rsi, r13
	lea rdi, [regsNames+4*11]
	call ncPrintReg

	mov rsi, r14
	lea rdi, [regsNames+4*12]
	call ncPrintReg

	mov rsi, r15
	lea rdi, [regsNames+4*13]
	call ncPrintReg

	lea rsi, [rsp+8]
	lea rdi, [regsNames+4*15]
	call ncPrintReg

	mov rsi, rbp
	lea rdi, [regsNames+4*16]
	call ncPrintReg

	mov rsi, $ ; Carga el valor de la direccion donde esta el mov (seria el IP) en rsi. El $ avanza en 1 con cada opcode (cada opcode ocupa 1 direccion de 1 byte).
	lea rdi, [regsNames+4*14]
	call ncPrintReg

	pop rsi
	pop rdi
	ret

_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5


;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

haltcpu:
	cli
	hlt
	ret

section .rodata
	; dd = 4 byte value. Hacemos un "array" donde cada posicion es de 4 bytes (cada caracter ocupa 1 byte, de esta forma todos terminan en 0)
	regsNames dd "rdi", "rsi", "rax", "rbx", "rcx", "rdx", "r8 ", "r9 ", "r10", "r11", "r12", "r13", "r14", "r15", "rip", "rsp", "rbp" ; 17 registros

section .bss
	aux resq 1
