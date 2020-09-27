        .text
        .globl errno
        .align  4

; socket(domain, type, protocol)
;
        .globl socket
socket:
        mv x10,x12
        mv x11,x13
        mv x12,x14
        li x17,198
        ecall
cerror:
        bge x10,x0,L.1
        la x17,errno
        sub x10,x0,x10
        sw x10,0(x17)
        li x10,-1
L.1:
        jalr x0,x1,0

; bind(fd, addr, len)
;
        .globl bind
bind:
        mv x10,x12
        mv x11,x13
        mv x12,x14
        li x17,200
        ecall
        jal x0,cerror

; listen(fd, backlog)
;
        .globl listen
listen:
        mv x10,x12
        mv x11,x13
        li x17,201
        ecall
        jal x0,cerror

; accept(fd, addr, len)
;
        .globl accept
accept:
        mv x10,x12
        mv x11,x13
        mv x12,x14
        li x17,202
        ecall
        jal x0,cerror

; connect(fd, addr, len)
;
        .globl connect
connect:
        mv x10,x12
        mv x11,x13
        mv x12,x14
        li x17,203
        ecall
        jal x0,cerror


