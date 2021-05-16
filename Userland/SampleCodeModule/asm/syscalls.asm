GLOBAL sys_write
GLOBAL getColor

section .text

getColor:
  mov rax, 74h
  ret

sys_write:
  mov rax, 1
  int 80h
  ret