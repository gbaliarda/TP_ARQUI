GLOBAL syscallHandler
EXTERN loadSysNum
EXTERN syscallDispatcher
GLOBAL getTimeRTC

SECTION .text

; en rax viene el numero de syscall a ejecutar
syscallHandler:
	pushState
  push rdi
  mov rdi, rax
  call loadSysNum
  pop rdi
  call syscallDispatcher
	popState
	iretq            ; ret especifico para volver de interrupciones    

%macro pushState 0
	; push rax 			 ; no pusheamos rax porque se usa luego para retornar en la syscall
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
	; pop rax
%endmacro

; ------------------- RTC -------------------------

getRTC:
	push rbp
	mov rbp, rsp
	push rbx
	mov rbx, [rbp+24]		; carga el puntero a la estructura

	xor rax, rax

	mov al, [rbp+16]		; parametro de que se quiere obtener
	out 70h, al				; escribo en la posicion 70h el parametro
	in al, 71h          	; Obtengo las horas/minutos/segundos según [rbp+16] 
	call BCDtoDec

	mov [rbx], eax	;guardo en la estructura el resultado, usando eax para que ocupe los 4bytes del int
	pop rbx
	leave
	ret

; Convierte un numero en formato BCD (binario codificado en decimal) el cual tiene las decenas en los higher 4 bits, y las unidades en los lower 4 bits. Recibe el BCD por al y lo retorna por ahi mismo.
BCDtoDec:
	mov dl, al
	mov cl, dl
	shr cl, 4			 ; shiftea cl 4 bits para la derecha (eliminando las unidades) y rellena con 0s a la derecha
	mov al, 10		 
	mul cl				 ; multiplico por 10 las decenas - ax = al * cl
	and dl, 0Fh		 ; me quedo con las unidades
	add dl, al		 ; formo el numero decimal listo para devolver (las decenas entran en al pues son numeros pequeños)
	mov al, dl		 ; guardo el resultado final en al para retornar
	ret

; 0 segundos 2 minutos 4 hora 7 dia 8 mes 9 anio 
%macro getData 1
	add rdi, 4
	push rdi
	push %1					; dato a obtener
	call getRTC
	add rsp, 16
%endmacro

getTimeRTC:
	push rbp
	mov rbp, rsp

	sub rdi, 4 ; 

	getData 4 ; horas
	getData 2 ; minutos		; ANDA
	getData 0 ; segundos
	getData 7 ; dia				; ANDA
	getData 8 ; mes
	getData 9 ; año

; 	mov eax, [rdi]
; 	add eax, esi
; 	cmp eax, 23
; 	jg  _newDay
; 	cmp eax, 0
; 	jl 	_prevDay
; 	jmp _end
; _newDay:    
; 	sub eax, 24
; 	jmp _end
; _prevDay:    
; 	add eax, 24
; 	jmp _end
; _end:        
; 	mov [rdi], eax
	leave
	ret
