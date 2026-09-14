/**
 * @brief Test program invoke interrupt but it's not enabled
 * @course University of Sydney ELEC3608 2026 Assignment 1
 * @author Rich Rademacher
 *
 */




/* Special note: see Unprivileged ISR pg 49, indicating the assembly writers created their own
   instruction, that is not consistent with the ISA */
.section .text
.global main
.global _start
_start:
    addi x1, x0, 0x8;       /* enable MIE bit */
    csrrs x0, mstatus, x1;
    /* MEIE not enabled */
    nop;
    addi x4, x0, 50;
    nop;
loop:
    addi x4, x4, -1;
    bne  x4, x0, loop;
    nop;
    ebreak;



/* Interrupt/Trap Vector (see sections.lds file for details) */
.section mtvec_section ,"ax",@progbits   /* this H0 section is "allocatiable, program code, executable" */

.global _mtvec

_mtvec:
    nop;                /* addr 0x1000 */
    addi x4, x0, 10;    /* addr 0x1004 */
loop1:
    addi x4, x4, -1;    /* addr 0x1008 */
    bne  x4, x0, loop1; /* addr 0x1010 */
    nop;                /* addr 0x1014 */
    ebreak;             /* addr 0x1018 */



/* expected result:
    expect h0:pc = 0x0020 (PC after ebreak)
    expect h0:x4 = 0x0 (count)
    expect h0:mcause = 0x0 (interrupt not taken)
    expect h0:mip = 0x800 (external interrupt in progress but not taken)
*/