    # place SP at the end of RAM
    li sp, 0x00010000

	li	a0,8
	jal ra,fib
	j quit

fib:
	addi	sp,sp,-16
	sw	s0,8(sp)
	sw	s1,4(sp)
	sw	s2,0(sp)
	sw	ra,12(sp)
	mv	s0,a0
	li	s1,0
	li	s2,1
L3:
	beq	zero,s0,L2
	beq	s0,s2,L2
	addi	a0,s0,-1
	jal ra,fib
	addi	s0,s0,-2
	add	s1,s1,a0
	j	L3
L2:
	add	a0,s0,s1
	lw	ra,12(sp)
	lw	s0,8(sp)
	lw	s1,4(sp)
	lw	s2,0(sp)
	addi	sp,sp,16
	jalr	x0,0(ra)

quit:
    ebreak
