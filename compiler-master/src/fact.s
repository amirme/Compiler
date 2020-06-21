.section .data
.section .text
.globl factorial
factorial:
      movq    $1, %rax
factorial_loop:
      cmpq    $1, %rdi
      jle     exit
      imulq   %rdi, %rax
      subq    $1, %rdi
      jmp     factorial_loop
exit:
      ret
