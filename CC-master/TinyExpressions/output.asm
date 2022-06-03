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
   push $1
   push $0
   push $0
   push %r12
   push %r13
   push %r14
   push %r15
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @3
   movq @3, %rdx
   movq %rdx, @1
   movq $1, @2
   movq @1, %rcx
   movq @2, 8(%rcx)
if0:
   movq %rbp, %rdi
   push %rdi
   call c
   movq %rax, @7
   addq $8, %rsp
   addq $0, %rsp
   cmp $0, @7
   je lazyAND0
   movq %rbp, %rdi
   push %rdi
   call c
   movq %rax, @8
   addq $8, %rsp
   addq $0, %rsp
lazyAND0:
   AND @7, @8
   movq @8, @6
   movq @6, %rax
   movq %rax, @5
   cmp $1, @5
   jne ifelse0
   movq $1, @9
   push %rbp
   movq %rsp, %rbp
   push %rax
   push %rcx
   push %rdx
   push %rdi
   push %rsi
   push @9
   movq @9, %rax
   call write
   pop @9
   pop %rsi
   pop %rdi
   pop %rdx
   pop %rcx
   pop %rax
   movq %rbp, %rsp
   pop %rbp
   jmp ifend0
ifelse0:
   movq $0, @11
   push %rbp
   movq %rsp, %rbp
   push %rax
   push %rcx
   push %rdx
   push %rdi
   push %rsi
   push @11
   movq @11, %rax
   call write
   pop @11
   pop %rsi
   pop %rdi
   pop %rdx
   pop %rcx
   pop %rax
   movq %rbp, %rsp
   pop %rbp
ifend0:
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
c:
   push %rbp
   movq %rsp, %rbp
   push $0
   push $1
   push $0
   push $0
   push %r12
   push %r13
   push %r14
   push %r15
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @15
   movq @15, %rdx
   movq %rdx, @13
   movq $0, @14
   movq @13, %rcx
   movq @14, 8(%rcx)
   push $0
   push $0
   movq %rbp, %rdi
   movq 16(%rdi), %rdi
   addq $0, %rdi
   movq %rdi, @17
   movq $0, @17
for0:
   cmp $100000, @17
   jg forend0
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @19
   movq @19, %rdx
   movq %rdx, @18
   movq @18, %rcx
   addq $1, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @24
   movq @24, %rdx
   movq %rdx, @23
   movq @23, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @21
   push %rbp
   movq %rsp, %rbp
   push %rax
   push %rcx
   push %rdx
   push %rdi
   push %rsi
   push @21
   movq @21, %rax
   call write
   pop @21
   pop %rsi
   pop %rdi
   pop %rdx
   pop %rcx
   pop %rax
   movq %rbp, %rsp
   pop %rbp
   addq $1, @17
   jmp for0
forend0:
   movq %rbp, %rdi
   movq 16(%rdi), %rdi
   addq $-32, %rdi
   movq %rdi, @28
   movq @28, %rdx
   movq %rdx, @26
   movq $0, @27
   movq @26, %rcx
   movq @27, 8(%rcx)
   movq $0, @30
   movq @30, %rax
   pop %r15
   pop %r14
   pop %r13
   pop %r12
   movq %rbp, %rsp
   pop %rbp
   ret
   pop %r15
   pop %r14
   pop %r13
   pop %r12
   addq $16, %rsp
   movq %rbp, %rsp
   pop %rbp
   ret
