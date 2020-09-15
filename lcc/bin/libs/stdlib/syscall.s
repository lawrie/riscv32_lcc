        .text
	.globl errno
        .align  4

; write(fd, buf, len)
;
	.globl write
	.globl _write
write:
_write:
        mv x10,x12
        mv x11,x13
        mv x12,x14
        li x17,64
        ecall
cerror:
        bge x10,x0,L.1
        la x17,errno
	sub x10,x0,x10
        sw x10,0(x17)
        li x10,-1
L.1:
        jalr x0,x1,0

; read(fd, buf, len);
;
	.globl read
	.globl _read
read:
_read:
	mv x10,x12
	mv x11,x13
	mv x12,x14
	li x17,63
	ecall
        jal x0,cerror

; open(path, flags, mode)
;
	.globl open
	.globl _open
open:
_open:
        li x10,-100	; AT_FDCWD
	mv x11,x12
	mv x12,x13
        li x13,420      ; mode 0644 for create
	li x17,56	; openat
	ecall
        jal x0,cerror

	.globl close
	.globl _close
close:
_close:
	mv x10,x12
	li x17,57
        ecall
	jal x0,cerror
	
; _exit(status)
;
	.globl _exit
_exit:
	mv x10,x12
	li x17,93
	ecall

	.globl lseek
	.globl _lseek
lseek:
_lseek:
	mv x10,x12
	mv x11,x13
	mv x12,x14
	li x17,63
	ecall
	jal x0,cerror

	.globl fstat
	.globl _fstat
fstat:
_fstat:
	mv x10,x12
	mv x11,x13
	li x17,80
	ecall
	jal x0,cerror

	.globl brk
brk:
	mv x10,x12
	li x17,214
	ecall
	jal x0,cerror

	.globl _isatty
_isatty:
	li x10,-1
        jalr x0,x1,0

