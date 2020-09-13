        .text
	.globl errno
        .align  4

; write(fd, buf, len)
;
	.globl write
write:
        mv x10,x12
        mv x11,x13
        mv x12,x14
        li x17,64
        ecall
cerror:
        beq x11,x0,L.1
        la x10,errno
        sw x11,0(x10)
        li x10,-1
L.1:
        jalr x0,x1,0

; read(fd, buf, len);
;
	.globl read
read:
	mv x10,x12
	mv x11,x13
	mv x12,x14
	li x17,63
	ecall
	beq x10,x10,cerror
        jalr x0,x1,0

; open(path, mode)
;
	.globl open
open:
	mv x10,x12
	mv x11,x13
	li x17,56
	ecall
	beq x10,x10,cerror
        jalr x0,x1,0

; _exit(status)
;
	.globl _exit
_exit:
	mv x10,x12
	li x17,93
	ecall

; <etc>
;

