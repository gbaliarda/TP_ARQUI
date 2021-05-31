GLOBAL throwInvalidOpcode
GLOBAL computeZeros

section .text

throwInvalidOpcode:
  ud2
  ret

computeZeros:
  ; cargamos los argumentos
  movq [a], xmm0               ; movq = move qword
  movq [b], xmm1
  movq [c], xmm2

  fild word [minusFour]        ; stack -4
  fld qword [a]                ; stack: a, -4
  fld qword [c]                ; stack: c, a, -4
  fmulp st1                    ; stack: a*c, -4
  fmulp st1                    ; stack: -4*a*c
  fld qword [b]
  fld qword [b]                ; stack: b, b, -4*a*c
  fmulp st1                    ; stack: b*b, -4*a*c
  faddp st1                    ; stack: b*b - 4*a*c

  ; checkeamos si el discriminante es negativo, en cuyo cortamos la ejecucion
  ftst                         ; test with 0
  fstsw ax
  sahf
  jb .no_real_solutions        ; if disc < 0, no real solutions

  fsqrt                        ; stack: sqrt(b*b - 4*a*c)
  fstp qword [disc]            ; store and pop stack
  fld1                         ; stack: 1.0
  fld qword [a]                ; stack: a, 1.0
  fscale                       ; stack: a * 2^(1.0) = 2*a, 1
  fdivp st1                    ; stack: 1/(2*a)
  fst qword [denom]            ; stack: 1/(2*a)
  fld qword [b]                ; stack: b, 1/(2*a)
  fld qword [disc]             ; stack: disc, b, 1/(2*a)
  fsubrp st1                   ; stack: disc - b, 1/(2*a)
  fmulp st1                    ; stack: (-b + disc)/(2*a)
  ; guardamos la primer raiz en el primer double * que nos pasan por parametro
  fstp qword [rdi]
  fld qword [b]                ; stack: b
  fld qword [disc]             ; stack: disc, b
  fchs                         ; stack: -disc, b
  fsubrp st1                   ; stack: -disc - b
  fmul qword [denom]           ; stack: (-b - disc)/(2*a)
  ; guardamos la segunda raiz en el segundo double *
  fstp qword [rsi]
  mov rax, 1
  jmp .exit
.no_real_solutions:
  ffree st0                    ; clean stack
  mov rax, 0                   ; return value is 0
.exit
  ret

section .data
  minusFour dw -4

section .bss
  a: resq 1
  b: resq 1
  c: resq 1
  disc: resq 1
  denom: resq 1