GLOBAL sys_write
GLOBAL sys_read
GLOBAL sys_inforeg
section .text

sys_read:
  mov rax, 0
  int 80h
  ret
sys_write:
  mov rax, 1
  int 80h
  ret

sys_inforeg:
  mov rax, 10
  int 80h
  ret