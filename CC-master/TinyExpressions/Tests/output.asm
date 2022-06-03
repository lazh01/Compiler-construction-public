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
   movq %rdi, @3
   movq @3, %rdx
   movq %rdx, @1
   movq $5, @2
   movq @2, %rax
   call allocL
   movq @1, %rdi
   movq %rax, 8(%rdi)
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, @7
   movq @7, %rdx
   movq %rdx, @5
   movq $0, @6
   movq @5, %rcx
   movq @6, 8(%rcx)
while0:
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, @14
   movq @14, %rdx
   movq %rdx, @13
   movq @13, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @11
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @18
   movq @18, %rdx
   movq %rdx, @17
   movq @17, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @16
   movq @16, %rsi
   movq 16(%rsi), @12
   cmp @12, @11
   jl explabel0
   movq $0, @10
   jmp expend0
explabel0:
   movq $1, @10
expend0:
   movq @10, %rax
   movq %rax, @9
   cmp $1, @9
   jne whileend0
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @24
   movq @24, %rdx
   movq %rdx, @22
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, @27
   movq @27, %rdx
   movq %rdx, @26
   movq @26, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @23
   movq @22, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @23, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @20
   movq $6, @21
   movq @21, %rax
   call allocL
   movq @20, %rdi
   movq %rax, 8(%rdi)
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, @31
   movq @31, %rdx
   movq %rdx, @29
   movq $0, @30
   movq @29, %rcx
   movq @30, 8(%rcx)
while1:
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, @38
   movq @38, %rdx
   movq %rdx, @37
   movq @37, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @35
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @44
   movq @44, %rdx
   movq %rdx, @42
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, @47
   movq @47, %rdx
   movq %rdx, @46
   movq @46, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @43
   movq @42, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @43, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @41
   movq @41, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @40
   movq @40, %rsi
   movq 16(%rsi), @36
   cmp @36, @35
   jl explabel1
   movq $0, @34
   jmp expend1
explabel1:
   movq $1, @34
expend1:
   movq @34, %rax
   movq %rax, @33
   cmp $1, @33
   jne whileend1
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @55
   movq @55, %rdx
   movq %rdx, @53
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, @58
   movq @58, %rdx
   movq %rdx, @57
   movq @57, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @54
   movq @53, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @54, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @51
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, @61
   movq @61, %rdx
   movq %rdx, @60
   movq @60, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @52
   movq @51, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @52, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @49
   movq $7, @50
   movq @50, %rax
   movq $1, %rdi
   call allocL
   movq @49, %rdi
   movq %rax, 8(%rdi)
   movq %rbp, %rdi
   addq $-80, %rdi
   movq %rdi, @65
   movq @65, %rdx
   movq %rdx, @63
   movq $0, @64
   movq @63, %rcx
   movq @64, 8(%rcx)
while2:
   movq %rbp, %rdi
   addq $-80, %rdi
   movq %rdi, @72
   movq @72, %rdx
   movq %rdx, @71
   movq @71, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @69
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @80
   movq @80, %rdx
   movq %rdx, @78
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, @83
   movq @83, %rdx
   movq %rdx, @82
   movq @82, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @79
   movq @78, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @79, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @76
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, @86
   movq @86, %rdx
   movq %rdx, @85
   movq @85, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @77
   movq @76, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @77, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @75
   movq @75, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @74
   movq @74, %rsi
   movq 16(%rsi), @70
   cmp @70, @69
   jl explabel2
   movq $0, @68
   jmp expend2
explabel2:
   movq $1, @68
expend2:
   movq @68, %rax
   movq %rax, @67
   cmp $1, @67
   jne whileend2
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @95
   movq @95, %rdx
   movq %rdx, @93
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, @98
   movq @98, %rdx
   movq %rdx, @97
   movq @97, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @94
   movq @93, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @94, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @91
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, @101
   movq @101, %rdx
   movq %rdx, @100
   movq @100, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @92
   movq @91, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @92, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @89
   movq %rbp, %rdi
   addq $-80, %rdi
   movq %rdi, @104
   movq @104, %rdx
   movq %rdx, @103
   movq @103, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @90
   movq @89, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @90, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @88
   movq $9, %rax
   push @88
   call getMem
   pop @88
   movq @88, %rcx
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
   movq %rdi, @116
   movq @116, %rdx
   movq %rdx, @114
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, @119
   movq @119, %rdx
   movq %rdx, @118
   movq @118, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @115
   movq @114, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @115, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @112
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, @122
   movq @122, %rdx
   movq %rdx, @121
   movq @121, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @113
   movq @112, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @113, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @110
   movq %rbp, %rdi
   addq $-80, %rdi
   movq %rdi, @125
   movq @125, %rdx
   movq %rdx, @124
   movq @124, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @111
   movq @110, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @111, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @108
   movq @108, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $0, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @106
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, @128
   movq @128, %rdx
   movq %rdx, @127
   movq @127, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @107
   movq @106, %rcx
   movq @107, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @140
   movq @140, %rdx
   movq %rdx, @138
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, @143
   movq @143, %rdx
   movq %rdx, @142
   movq @142, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @139
   movq @138, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @139, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @136
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, @146
   movq @146, %rdx
   movq %rdx, @145
   movq @145, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @137
   movq @136, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @137, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @134
   movq %rbp, %rdi
   addq $-80, %rdi
   movq %rdi, @149
   movq @149, %rdx
   movq %rdx, @148
   movq @148, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @135
   movq @134, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @135, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @132
   movq @132, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $1, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @130
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, @152
   movq @152, %rdx
   movq %rdx, @151
   movq @151, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @131
   movq @130, %rcx
   movq @131, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @164
   movq @164, %rdx
   movq %rdx, @162
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, @167
   movq @167, %rdx
   movq %rdx, @166
   movq @166, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @163
   movq @162, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @163, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @160
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, @170
   movq @170, %rdx
   movq %rdx, @169
   movq @169, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @161
   movq @160, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @161, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @158
   movq %rbp, %rdi
   addq $-80, %rdi
   movq %rdi, @173
   movq @173, %rdx
   movq %rdx, @172
   movq @172, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @159
   movq @158, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @159, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @156
   movq @156, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $2, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @154
   movq %rbp, %rdi
   addq $-80, %rdi
   movq %rdi, @176
   movq @176, %rdx
   movq %rdx, @175
   movq @175, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @155
   movq @154, %rcx
   movq @155, 8(%rcx)
   movq %rbp, %rdi
   addq $-80, %rdi
   movq %rdi, @180
   movq @180, %rdx
   movq %rdx, @178
   movq %rbp, %rdi
   addq $-80, %rdi
   movq %rdi, @185
   movq @185, %rdx
   movq %rdx, @184
   movq @184, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @182
   movq $1, @183
   movq @182, %rax
   addq @183, %rax
   movq %rax, @179
   movq @178, %rcx
   movq @179, 8(%rcx)
   jmp while2
whileend2:
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, @189
   movq @189, %rdx
   movq %rdx, @187
   movq %rbp, %rdi
   addq $-64, %rdi
   movq %rdi, @194
   movq @194, %rdx
   movq %rdx, @193
   movq @193, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @191
   movq $1, @192
   movq @191, %rax
   addq @192, %rax
   movq %rax, @188
   movq @187, %rcx
   movq @188, 8(%rcx)
   jmp while1
whileend1:
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, @198
   movq @198, %rdx
   movq %rdx, @196
   movq %rbp, %rdi
   addq $-48, %rdi
   movq %rdi, @203
   movq @203, %rdx
   movq %rdx, @202
   movq @202, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @200
   movq $1, @201
   movq @200, %rax
   addq @201, %rax
   movq %rax, @197
   movq @196, %rcx
   movq @197, 8(%rcx)
   jmp while0
whileend0:
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @222
   movq @222, %rdx
   movq %rdx, @220
   movq $4, @221
   movq @220, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @221, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @218
   movq $5, @219
   movq @218, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @219, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @216
   movq $6, @217
   movq @216, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @217, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @214
   movq @214, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $0, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @213
   movq @213, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @211
   movq $100, @212
   movq @211, %rax
   imulq @212, %rax
   movq %rax, @209
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @235
   movq @235, %rdx
   movq %rdx, @233
   movq $4, @234
   movq @233, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @234, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @231
   movq $5, @232
   movq @231, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @232, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @229
   movq $6, @230
   movq @229, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @230, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @227
   movq @227, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $1, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @226
   movq @226, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @224
   movq $10, @225
   movq @224, %rax
   imulq @225, %rax
   movq %rax, @210
   movq @209, %rax
   addq @210, %rax
   movq %rax, @207
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @246
   movq @246, %rdx
   movq %rdx, @244
   movq $4, @245
   movq @244, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @245, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @242
   movq $5, @243
   movq @242, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @243, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @240
   movq $6, @241
   movq @240, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @241, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @238
   movq @238, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $2, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @237
   movq @237, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @208
   movq @207, %rax
   addq @208, %rax
   movq %rax, @205
   push %rbp
   movq %rsp, %rbp
   push %rax
   push %rcx
   push %rdx
   push %rdi
   push %rsi
   push @205
   movq @205, %rax
   call write
   pop @205
   pop %rsi
   pop %rdi
   pop %rdx
   pop %rcx
   pop %rax
   movq %rbp, %rsp
   pop %rbp
   movq %rbp, %rdi
   addq $-96, %rdi
   movq %rdi, @250
   movq @250, %rdx
   movq %rdx, @248
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @259
   movq @259, %rdx
   movq %rdx, @257
   movq $4, @258
   movq @257, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @258, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @255
   movq $5, @256
   movq @255, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @256, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @253
   movq $6, @254
   movq @253, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @254, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @252
   movq @252, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @249
   movq @248, %rcx
   movq @249, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @269
   movq @269, %rdx
   movq %rdx, @267
   movq $4, @268
   movq @267, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @268, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @265
   movq $5, @266
   movq @265, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @266, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @263
   movq $6, @264
   movq @263, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @264, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @261
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @278
   movq @278, %rdx
   movq %rdx, @276
   movq $4, @277
   movq @276, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @277, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @274
   movq $5, @275
   movq @274, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @275, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @272
   movq $5, @273
   movq @272, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @273, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @271
   movq @271, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @262
   movq @261, %rcx
   movq @262, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @288
   movq @288, %rdx
   movq %rdx, @286
   movq $4, @287
   movq @286, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @287, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @284
   movq $5, @285
   movq @284, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @285, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @282
   movq $5, @283
   movq @282, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @283, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @280
   movq %rbp, %rdi
   addq $-96, %rdi
   movq %rdi, @291
   movq @291, %rdx
   movq %rdx, @290
   movq @290, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @281
   movq @280, %rcx
   movq @281, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @310
   movq @310, %rdx
   movq %rdx, @308
   movq $4, @309
   movq @308, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @309, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @306
   movq $5, @307
   movq @306, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @307, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @304
   movq $6, @305
   movq @304, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @305, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @302
   movq @302, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $0, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @301
   movq @301, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @299
   movq $100, @300
   movq @299, %rax
   imulq @300, %rax
   movq %rax, @297
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @323
   movq @323, %rdx
   movq %rdx, @321
   movq $4, @322
   movq @321, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @322, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @319
   movq $5, @320
   movq @319, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @320, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @317
   movq $6, @318
   movq @317, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @318, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @315
   movq @315, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $1, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @314
   movq @314, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @312
   movq $10, @313
   movq @312, %rax
   imulq @313, %rax
   movq %rax, @298
   movq @297, %rax
   addq @298, %rax
   movq %rax, @295
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @334
   movq @334, %rdx
   movq %rdx, @332
   movq $4, @333
   movq @332, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @333, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @330
   movq $5, @331
   movq @330, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @331, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @328
   movq $6, @329
   movq @328, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @329, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @326
   movq @326, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $2, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @325
   movq @325, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @296
   movq @295, %rax
   addq @296, %rax
   movq %rax, @293
   push %rbp
   movq %rsp, %rbp
   push %rax
   push %rcx
   push %rdx
   push %rdi
   push %rsi
   push @293
   movq @293, %rax
   call write
   pop @293
   pop %rsi
   pop %rdi
   pop %rdx
   pop %rcx
   pop %rax
   movq %rbp, %rsp
   pop %rbp
   movq %rbp, %rdi
   addq $-112, %rdi
   movq %rdi, @338
   movq @338, %rdx
   movq %rdx, @336
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @345
   movq @345, %rdx
   movq %rdx, @343
   movq $4, @344
   movq @343, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @344, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @341
   movq $5, @342
   movq @341, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @342, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @340
   movq @340, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @337
   movq @336, %rcx
   movq @337, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @353
   movq @353, %rdx
   movq %rdx, @351
   movq $4, @352
   movq @351, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @352, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @349
   movq $5, @350
   movq @349, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @350, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @347
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @360
   movq @360, %rdx
   movq %rdx, @358
   movq $4, @359
   movq @358, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @359, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @356
   movq $4, @357
   movq @356, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @357, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @355
   movq @355, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @348
   movq @347, %rcx
   movq @348, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @368
   movq @368, %rdx
   movq %rdx, @366
   movq $4, @367
   movq @366, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @367, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @364
   movq $4, @365
   movq @364, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @365, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @362
   movq %rbp, %rdi
   addq $-112, %rdi
   movq %rdi, @371
   movq @371, %rdx
   movq %rdx, @370
   movq @370, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @363
   movq @362, %rcx
   movq @363, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @390
   movq @390, %rdx
   movq %rdx, @388
   movq $4, @389
   movq @388, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @389, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @386
   movq $5, @387
   movq @386, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @387, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @384
   movq $6, @385
   movq @384, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @385, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @382
   movq @382, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $0, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @381
   movq @381, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @379
   movq $100, @380
   movq @379, %rax
   imulq @380, %rax
   movq %rax, @377
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @403
   movq @403, %rdx
   movq %rdx, @401
   movq $4, @402
   movq @401, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @402, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @399
   movq $5, @400
   movq @399, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @400, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @397
   movq $6, @398
   movq @397, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @398, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @395
   movq @395, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $1, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @394
   movq @394, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @392
   movq $10, @393
   movq @392, %rax
   imulq @393, %rax
   movq %rax, @378
   movq @377, %rax
   addq @378, %rax
   movq %rax, @375
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @414
   movq @414, %rdx
   movq %rdx, @412
   movq $4, @413
   movq @412, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @413, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @410
   movq $5, @411
   movq @410, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @411, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @408
   movq $6, @409
   movq @408, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @409, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @406
   movq @406, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $2, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @405
   movq @405, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @376
   movq @375, %rax
   addq @376, %rax
   movq %rax, @373
   push %rbp
   movq %rsp, %rbp
   push %rax
   push %rcx
   push %rdx
   push %rdi
   push %rsi
   push @373
   movq @373, %rax
   call write
   pop @373
   pop %rsi
   pop %rdi
   pop %rdx
   pop %rcx
   pop %rax
   movq %rbp, %rsp
   pop %rbp
   movq %rbp, %rdi
   addq $-128, %rdi
   movq %rdi, @418
   movq @418, %rdx
   movq %rdx, @416
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @423
   movq @423, %rdx
   movq %rdx, @421
   movq $4, @422
   movq @421, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @422, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @420
   movq @420, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @417
   movq @416, %rcx
   movq @417, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @429
   movq @429, %rdx
   movq %rdx, @427
   movq $4, @428
   movq @427, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @428, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @425
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @434
   movq @434, %rdx
   movq %rdx, @432
   movq $3, @433
   movq @432, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @433, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @431
   movq @431, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @426
   movq @425, %rcx
   movq @426, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @440
   movq @440, %rdx
   movq %rdx, @438
   movq $3, @439
   movq @438, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @439, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @436
   movq %rbp, %rdi
   addq $-128, %rdi
   movq %rdi, @443
   movq @443, %rdx
   movq %rdx, @442
   movq @442, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @437
   movq @436, %rcx
   movq @437, 8(%rcx)
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @462
   movq @462, %rdx
   movq %rdx, @460
   movq $4, @461
   movq @460, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @461, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @458
   movq $5, @459
   movq @458, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @459, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @456
   movq $6, @457
   movq @456, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @457, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @454
   movq @454, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $0, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @453
   movq @453, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @451
   movq $100, @452
   movq @451, %rax
   imulq @452, %rax
   movq %rax, @449
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @475
   movq @475, %rdx
   movq %rdx, @473
   movq $4, @474
   movq @473, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @474, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @471
   movq $5, @472
   movq @471, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @472, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @469
   movq $6, @470
   movq @469, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @470, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @467
   movq @467, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $1, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @466
   movq @466, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @464
   movq $10, @465
   movq @464, %rax
   imulq @465, %rax
   movq %rax, @450
   movq @449, %rax
   addq @450, %rax
   movq %rax, @447
   movq %rbp, %rdi
   addq $-32, %rdi
   movq %rdi, @486
   movq @486, %rdx
   movq %rdx, @484
   movq $4, @485
   movq @484, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @485, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @482
   movq $5, @483
   movq @482, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @483, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @480
   movq $6, @481
   movq @480, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq @481, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @478
   movq @478, %rdx
   movq 8(%rdx), %rsi
   addq $24, %rsi
   movq $2, %rax
   movq $16, %rdi
   imulq %rdi
   addq %rax, %rsi
   movq %rsi, @477
   movq @477, %rcx
   movq 8(%rcx), %rdi
   movq %rdi, @448
   movq @447, %rax
   addq @448, %rax
   movq %rax, @445
   push %rbp
   movq %rsp, %rbp
   push %rax
   push %rcx
   push %rdx
   push %rdi
   push %rsi
   push @445
   movq @445, %rax
   call write
   pop @445
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
