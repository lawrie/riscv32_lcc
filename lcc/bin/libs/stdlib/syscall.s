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
        mv x13,x14
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
	mv x13,x15
	li x17,62
	ecall
	jal x0,cerror

	.globl statx
	.globl _statx
statx:
_statx:
	mv x10,x12
	mv x11,x13
	mv x12,x14
	mv x13,x15
	mv x14,x16
	li x17,291
	ecall
	jal x0,cerror

	.globl _fstat
_fstat:			; Needs fixing
	li x10,-1
        jalr x0,x1,0


	.globl _brk
_brk:
	mv x10,x12
	li x17,214
	ecall
        jalr x0,x1,0

	.globl getcwd
	.globl _getcwd
getcwd:
_getcwd:
	mv x10,x12
	mv x11,x13
	mv x12,x14
	li x17,17
	ecall
	jal x0,cerror

	.globl dup
	.globl _dup
dup:
_dup:
	mv x10,x12
	li x17,23
	ecall
	jal x0,cerror

	.globl dup3
	.globl _dup3
dup3:
_dup3:
	mv x10,x12
	mv x11,x13
	mv x12,x14
	li x17,24
	ecall
	jal x0,cerror

	.globl getpid
	.globl _getpid
getpid:
_getpid:
	li x17,172
	ecall
	jal x0,cerror

	.globl getppid
	.globl _getppid
getppid:
_getppid:
	li x17,173
	ecall
	jal x0,cerror

	.globl getuid
	.globl _getuid
getuid:
_getuid:
	li x17,174
	ecall
	jal x0,cerror

	.globl geteuid
	.globl _geteuid
geteuid:
_geteuid:
	li x17,175
	ecall
	jal x0,cerror

	.globl getgid
	.globl _getgid
getgid:
_getgid:
	li x17,176
	ecall
	jal x0,cerror

	.globl getegid
	.globl _getegid
getegid:
_getegid:
	li x17,177
	ecall
	jal x0,cerror

	.globl gettid
	.globl _gettid
gettid:
_gettid:
	li x17,178
	ecall
	jal x0,cerror

	.globl sysinfo
	.globl _sysinfo
sysinfo:
_sysinfo:
	mv x10,x12
	li x17,179
	ecall
	jal x0,cerror

	.globl setuid
	.globl _setuid
setuid:
_setuid:
	mv x10,x12
	li x17,146
	ecall
	jal x0,cerror

	.globl setgid
	.globl _setgid
setgid:
_setgid:
	mv x10,x12
	li x17,144
	ecall
	jal x0,cerror

	.globl chdir
	.globl _chdir
chdir:
_chdir:
	mv x10,x12
	li x17,49
	ecall
	jal x0,cerror

	.globl chmod
	.globl _chmod
chmod:
_chmod:
	mv x10,x12
	mv x11,x13
	li x17,52
	ecall
	jal x0,cerror

	.globl times
	.globl _times
times:
_times:
	mv x10,x12
	li x17,153
	ecall
	jal x0,cerror

	.globl mount
	.globl _mount
mount:
_mount:
	mv x10,x12
	mv x11,x13
	mv x12,x14
	mv x13,x15
	mv x14,x16
	li x17,40
	ecall
	jal x0,cerror

	.globl umount2
	.globl _umount2
umount2:
_umount2:
	mv x10,x12
	mv x11,x13
	li x17,39
	ecall
	jal x0,cerror

	.globl kill
	.globl _kill
kill:
_kill:
	mv x10,x12
	mv x11,x13
	li x17,129
	ecall
	jal x0,cerror

	.globl linkat
	.globl _linkat
linkat:
_linkat:
	mv x10,x12
	mv x11,x13
	mv x12,x14
	mv x13,x15
	mv x14,x16
	li x17,37
	ecall
	jal x0,cerror

	.globl unlinkat
	.globl _unlinkat
unlinkat:
_unlinkat:
	mv x10,x12
	mv x11,x13
	mv x12,x14
	li x17,35
	ecall
	jal x0,cerror

	.globl unlink
unlink:
	li x10,-100
	mv x11,x13
	li x12,0
	li x17,35
	ecall
	jal x0,cerror

	.globl utimensat
	.globl _utimensat
utimensat:
_utimensat:
	mv x10,x12
	mv x11,x13
	mv x12,x14
	mv x13,x15
	li x17,88
	ecall
	jal x0,cerror

	.globl fork
fork:
	li x10, 17	; SIGCHILD
	mv x11, x2
	li x17,	220	; __NR_clone
	ecall
	jal x0,cerror


	.globl execve
execve:
	mv x10,x12
	mv x11,x13
	mv x12,x14
	li x17,221
	ecall
	jal x0,cerror

	.globl waitid
waitid:
	mv x10,x12
	mv x11,x13
	mv x12,x14
	li x17,95
	ecall
	jal x0,cerror

	.globl nanosleep
nanosleep:
	mv x10,x12
	mv x11,x13
	li x17,101
	ecall
	jal x0,cerror

	.globl ioctl
	.globl _ioctl
ioctl:
_ioctl:
	mv x10,x12
	mv x11,x13
	mv x12,x14
	li x17,29
	ecall
	jal x0,cerror

	.globl pipe2
	.globl _pipe2
pipe2:
_pipe2:
	mv x10,x12
	mv x11,x13
	li x17,59
	ecall
	jal x0,cerror

	.globl mknod
	.globl _mknod
mknod:
_mknod:
	mv x10,x12
	mv x11,x13
	mv x12,x14
	mv x13,x15
	li x17,33
	ecall
	jal x0,cerror

	.globl faccess2
faccess2:
	mv x10,x12
	mv x11,x13
	mv x12,x14
	mv x13,x15
	li x17,439
	ecall
	jal x0,cerror

	.globl mkdirat
mkdirat:
	mv x10,x12
	mv x11,x13
	mv x12,x14
	li x17,34
	ecall
	jal x0,cerror

	.globl umask
	.globl _umask
umask:
_umask:
	mv x10,x12
	li x17,166
	ecall
	jal x0,cerror

	.globl gettimeofday
	.globl _gettimeofday
gettimeofday:
_gettimeofday:
	mv x10,x12
	mv x11,x13
	li x17,169
	ecall
	jal x0,cerror

	.globl settimeofday
	.globl _settimeofday
settimeofday:
_settimeofday:
	mv x10,x12
	mv x11,x13
	li x17,170
	ecall
	jal x0,cerror

	.globl getpriority
	.globl _getpriority
getpriority:
_getpriority:
	mv x10,x12
	mv x11,x13
	li x17,141
	ecall
	jal x0,cerror

	.globl setpriority
	.globl _setpriority
setpriority:
_setpriority:
	mv x10,x12
	mv x11,x13
	mv x12,x14
	li x17,140
	ecall
	jal x0,cerror

	.globl clock_gettime
	.globl _clock_gettime
clock_gettime:
_clock_gettime:
	mv x10,x12
	mv x11,x13
	li x17,113
	ecall
	jal x0,cerror

	.globl clock_settime
	.globl _clock_settime
clock_settime:
_clock_settime:
	mv x10,x12
	mv x11,x13
	li x17,112
	ecall
	jal x0,cerror

	.globl sigaction
	.globl _sigaction
sigaction:
_sigaction:
	mv x10,x12
	mv x11,x13
	mv x12,x14
	li x17,134
	ecall
	jal x0,cerror

	.globl sync
	.globl _sync
sync:
_sync:
	li x17,81
	ecall
	jal x0,cerror

	.globl _isatty
_isatty:
	li x10,1
        jalr x0,x1,0

