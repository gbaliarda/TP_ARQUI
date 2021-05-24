GLOBAL throwInvalidOpcode

section .text

throwInvalidOpcode:
  ud2
  ret