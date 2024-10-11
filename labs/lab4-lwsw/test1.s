.section .text
.global _start
_start:
    addi x1, zero, 0xd0
    addi sp, zero, 0x24
	sw	x1,0(sp)
    addi sp,sp,-4
    lw  x10,4(sp)
    fence
