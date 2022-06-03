.section .data
   initialBrk: .quad 0
   currentBrk: .quad 0
   newBrk: .quad 0
   freelist: .quad 0
   Callstack: .space 400
   top: .quad 0
.section .text
.globl main

main:
   movq $12, %rax
   movq $0, %rdi
   syscall
   movq %rax, (initialBrk)
   movq %rax, (currentBrk)
   movq %rax, (newBrk)
   movq $Callstack, (top)
   push %rbp
   movq %rsp, %rbp
   call pushframe
   push $0
   push $2
   push $0
   push $1
   push $0
   push $1
   push %r12
   push %r13
   push %r14
   push %r15
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, @3
   movq @3, %rdx
   movq %rdx, @1
   movq $7, @2
   movq @2, %rax
   call allocL
   movq @1, %rdi
   movq %rax, 8(%rdi)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @7
   movq @7, %rdx
   movq %rdx, @5
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, @10
   movq @10, %rdx
   movq %rdx, @9
   movq @9, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @6
   movq @5, %rcx
   movq @6, 8(%rcx)
   movq $42, @12
   push %rbp
   movq %rsp, %rbp
   push %rax
   push %rcx
   push %rdx
   push %rdi
   push %rsi
   push @12
   movq @12, %rax
   call write
   pop @12
   pop %rsi
   pop %rdi
   pop %rdx
   pop %rcx
   pop %rax
   movq %rbp, %rsp
   pop %rbp
   pop %r15
   pop %r14
   pop %r13
   pop %r12
   pop %rax
   pop %rax
   call popframe
   movq %rbp, %rsp
   pop %rbp
   movq $60, %rax
   movq $0, %rdi
   syscall

getMem:
   push %r12
   push %r13
   push %r14
   push %r15
   push %r11
   push %r10
   push %r9
   push %r8
   push %rdi
   push %rsi
   push %rdx
   push %rcx
   push %rbx
   movq (currentBrk), %rdi
   movq $8, %rdx
   imulq %rdx
   addq %rax, %rdi
   movq $12, %rax
   syscall
   movq %rax, (newBrk)
   movq %rax, (currentBrk);
   pop %rbx
   pop %rcx
   pop %rdx
   pop %rsi
   pop %rdi
   pop %r8
   pop %r9
   pop %r10
   pop %r11
   pop %r15
   pop %r14
   pop %r13
   pop %r12
   ret
allocL:
   movq %rax, %rsi
   movq $2, %rcx
   imulq %rcx
   addq $3, %rax
   movq %rax, %rcx
   push %rdi
   call getMem
   pop %rdi
   movq $0, (%rax)
   movq %rcx, 8(%rax)
   movq %rsi, 16(%rax)
   movq %rax, %rcx
   addq $24, %rcx
allocLloop:
   cmp $0, %rsi
   je allocLloopEnd
   movq %rdi, (%rcx)
   movq $0, 8(%rcx)
   addq $16, %rcx
   subq $1, %rsi
   jmp allocLloop
allocLloopEnd:
   ret
popframe:
   subq $8, (top)
   movq (top), %rax
   movq $0, (%rax)
   ret
pushframe:
   movq (top), %rax
   movq %rbp, (%rax)
   addq $8, (top)
   ret
write:
   push %rbp
   movq %rsp, %rbp
   push %rax
   push %r11
   push %r10
   push %r9
   push %r8
   push %rdi
   push %rsi
   push %rdx
   push %rcx
   push %rbx
   push %r12
   push %r13
   push %r14
   push %r15
   movq $0, %r15
   movq %rax, %r14
   push $10
   addq $1, %r15
   cmp $0, %r14
   jge positive
   push $45
   movq $1, %rax
   movq $1, %rdi
   movq %rsp, %rsi
   movq $1, %rdx
   syscall
   addq $8, %rsp
   movq %r14, %rsi
   neg %rsi
   movq %rsi, %r14
   movq %r14, %rax
   jmp writeloop
positive:
   movq %r14, %rax
writeloop: 
   movq $0, %rdx
   movq $10, %rcx
   idivq %rcx
   addq $48, %rdx
   push %rdx
   addq $1, %r15
   cmp $0, %rax
   jne writeloop
printloop:
   movq $1, %rax
   movq $1, %rdi
   movq %rsp, %rsi
   movq $1, %rdx
   syscall
   addq $8, %rsp
   addq $-1, %r15
   cmp $0, %r15
   jne printloop
   pop %r15
   pop %r14
   pop %r13
   pop %r12
   pop %rbx
   pop %rcx
   pop %rdx
   pop %rsi
   pop %rdi
   pop %r8
   pop %r9
   pop %r10
   pop %r11
   pop %rax
   movq %rbp, %rsp
   pop %rbp
   ret
