.section .data
   spilling: .space 0
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
   push $7
   push $0
   push $1
   push $0
   push $0
   push $0
   push $0
   push $0
   push $0
   push $0
   push $1
   push $0
   push $1
   push $0
   push $1
   push %r12
   push %r13
   push %r14
   push %r15
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq $5, %r14
   movq %r14, %rax
   call allocL
   movq %r15, %rdi
   movq %rax, 8(%rdi)
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq $0, %r14
   movq %r15, %rcx
   movq %r14, 8(%rcx)
while0:
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq %r15, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r15
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r14, %rsi
   movq 16(%rsi), %r14
   cmp %r14, %r15
   jl explabel0
   movq $0, %r15
   jmp expend0
explabel0:
   movq $1, %r15
expend0:
   movq %r15, %rax
   movq %rax, %r15
   cmp $1, %r15
   jne whileend0
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq $6, %r14
   movq %r14, %rax
   call allocL
   movq %r15, %rdi
   movq %rax, 8(%rdi)
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq $0, %r14
   movq %r15, %rcx
   movq %r14, 8(%rcx)
while1:
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq %r15, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r15
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, %r13
   movq %r13, %rdx
   movq %rdx, %r13
   movq %r13, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r14, %rsi
   movq 16(%rsi), %r14
   cmp %r14, %r15
   jl explabel1
   movq $0, %r15
   jmp expend1
explabel1:
   movq $1, %r15
expend1:
   movq %r15, %rax
   movq %rax, %r15
   cmp $1, %r15
   jne whileend1
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq $7, %r14
   movq %r14, %rax
   movq $1, %rdi
   call allocL
   movq %r15, %rdi
   movq %rax, 8(%rdi)
   movq %rbp, %rdi
   addq $-80, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq $0, %r14
   movq %r15, %rcx
   movq %r14, 8(%rcx)
while2:
   movq %rbp, %rdi
   addq $-80, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq %r15, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r15
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, %r13
   movq %r13, %rdx
   movq %rdx, %r13
   movq %r13, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, %r13
   movq %r13, %rdx
   movq %rdx, %r13
   movq %r13, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r14, %rsi
   movq 16(%rsi), %r14
   cmp %r14, %r15
   jl explabel2
   movq $0, %r15
   jmp expend2
explabel2:
   movq $1, %r15
expend2:
   movq %r15, %rax
   movq %rax, %r15
   cmp $1, %r15
   jne whileend2
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %rbp, %rdi
   addq $-80, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq $9, %rax
   push %r15
   call getMem
   call write
   pop %r15
   movq %r15, %rcx
   movq %rax, 8(%rcx)
   movq $0, (%rax)
   movq $9, 8(%rax)
   movq $3, 16(%rax)
   movq $0, 24(%rax)
   movq $0, 32(%rax)
   movq $0, 40(%rax)
   movq $0, 48(%rax)
   movq $0, 56(%rax)
   movq $0, 64(%rax)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %rbp, %rdi
   addq $-80, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $0, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rcx
   movq %r14, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %rbp, %rdi
   addq $-80, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $1, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rcx
   movq %r14, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %rbp, %rdi
   addq $-80, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $2, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %rbp, %rdi
   addq $-80, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rcx
   movq %r14, 8(%rcx)
   movq %rbp, %rdi
   addq $-80, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq %rbp, %rdi
   addq $-80, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq $1, %r13
   movq %r14, %rax
   addq %r13, %rax
   movq %rax, %r14
   movq %r15, %rcx
   movq %r14, 8(%rcx)
   jmp while2
whileend2:
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq $1, %r13
   movq %r14, %rax
   addq %r13, %rax
   movq %rax, %r14
   movq %r15, %rcx
   movq %r14, 8(%rcx)
   jmp while1
whileend1:
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq $1, %r13
   movq %r14, %rax
   addq %r13, %rax
   movq %rax, %r14
   movq %r15, %rcx
   movq %r14, 8(%rcx)
   jmp while0
whileend0:
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq $4, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq $5, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq $6, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $0, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %r15, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r15
   movq $100, %r14
   movq %r15, %rax
   imulq %r14, %rax
   movq %rax, %r15
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq $4, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $5, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $6, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $1, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq $10, %r13
   movq %r14, %rax
   imulq %r13, %rax
   movq %rax, %r14
   movq %r15, %rax
   addq %r14, %rax
   movq %rax, %r15
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq $4, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $5, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $6, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $2, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rax
   addq %r14, %rax
   movq %rax, %r15
   push %rbp
   movq %rsp, %rbp
   push %rax
   push %rcx
   push %rdx
   push %rdi
   push %rsi
   push %r15
   movq %r15, %rax
   call write
   pop %r15
   pop %rsi
   pop %rdi
   pop %rdx
   pop %rcx
   pop %rax
   movq %rbp, %rsp
   pop %rbp
   movq %rbp, %rdi
   addq $-96, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq $4, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $5, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $6, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rcx
   movq %r14, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq $4, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq $5, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq $6, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq $4, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $5, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $5, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rcx
   movq %r14, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq $4, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq $5, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq $5, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %rbp, %rdi
   addq $-96, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rcx
   movq %r14, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq $4, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq $5, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq $6, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $0, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %r15, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r15
   movq $100, %r14
   movq %r15, %rax
   imulq %r14, %rax
   movq %rax, %r15
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq $4, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $5, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $6, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $1, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq $10, %r13
   movq %r14, %rax
   imulq %r13, %rax
   movq %rax, %r14
   movq %r15, %rax
   addq %r14, %rax
   movq %rax, %r15
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq $4, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $5, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $6, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $2, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rax
   addq %r14, %rax
   movq %rax, %r15
   push %rbp
   movq %rsp, %rbp
   push %rax
   push %rcx
   push %rdx
   push %rdi
   push %rsi
   push %r15
   movq %r15, %rax
   call write
   pop %r15
   pop %rsi
   pop %rdi
   pop %rdx
   pop %rcx
   pop %rax
   movq %rbp, %rsp
   pop %rbp
   movq %rbp, %rdi
   addq $-112, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq $4, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $5, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rcx
   movq %r14, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq $4, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq $5, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq $4, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $4, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rcx
   movq %r14, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq $4, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq $4, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %rbp, %rdi
   addq $-112, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rcx
   movq %r14, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq $4, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq $5, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq $6, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $0, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %r15, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r15
   movq $100, %r14
   movq %r15, %rax
   imulq %r14, %rax
   movq %rax, %r15
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq $4, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $5, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $6, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $1, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq $10, %r13
   movq %r14, %rax
   imulq %r13, %rax
   movq %rax, %r14
   movq %r15, %rax
   addq %r14, %rax
   movq %rax, %r15
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq $4, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $5, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $6, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $2, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rax
   addq %r14, %rax
   movq %rax, %r15
   push %rbp
   movq %rsp, %rbp
   push %rax
   push %rcx
   push %rdx
   push %rdi
   push %rsi
   push %r15
   movq %r15, %rax
   call write
   pop %r15
   pop %rsi
   pop %rdi
   pop %rdx
   pop %rcx
   pop %rax
   movq %rbp, %rsp
   pop %rbp
   movq %rbp, %rdi
   addq $-128, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq $4, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rcx
   movq %r14, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq $4, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq $3, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rcx
   movq %r14, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq $3, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %rbp, %rdi
   addq $-128, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rcx
   movq %r14, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r15
   movq %r15, %rdx
   movq %rdx, %r15
   movq $4, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq $5, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq $6, %r14
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r14, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %r15, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $0, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r15
   movq %r15, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r15
   movq $100, %r14
   movq %r15, %rax
   imulq %r14, %rax
   movq %rax, %r15
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq $4, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $5, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $6, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $1, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq $10, %r13
   movq %r14, %rax
   imulq %r13, %rax
   movq %rax, %r14
   movq %r15, %rax
   addq %r14, %rax
   movq %rax, %r15
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, %r14
   movq %r14, %rdx
   movq %rdx, %r14
   movq $4, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $5, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq $6, %r13
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq %r13, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $2, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, %r14
   movq %r14, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, %r14
   movq %r15, %rax
   addq %r14, %rax
   movq %rax, %r15
   push %rbp
   movq %rsp, %rbp
   push %rax
   push %rcx
   push %rdx
   push %rdi
   push %rsi
   push %r15
   movq %r15, %rax
   call write
   pop %r15
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
