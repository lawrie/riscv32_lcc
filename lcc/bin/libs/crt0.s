	.text
	.align    4
	.globl    main

_start:
	lw x12, 0(x2)	; a0 = argc
	addi x13, x2, 4	; a1 = argv
	addi x14, x2, 8	; a2 = envp
	addi x2, x2, -16
	andi x2, x2, -16

	jal x1,main	; x10 = main(argc, argv, env)

	li x17,93	; exit(x10);
	ecall

