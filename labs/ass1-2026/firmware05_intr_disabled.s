/**
 * @brief Test program to test disabled interrupts
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
    /* MIE (global) is not enabled */
    addi x1, x0, 1;
    slli x1, x1, 11;       /* enable MEIE bit */
    csrrs x0, mie, x1;
    nop;
    addi x4, x0, 50;
    nop;
loop:
    addi x4, x4, -1;
    bne  x4, x0, loop;
    nop;
    ebreak;  /* addr 0x0028 */



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
    expect h0:pc = 0x0028 (PC after ebreak)
    expect h0:x4 = 0x0 (count)
    expect h0:mcause = 0x00 (interrupt not taken)
    expect h0:mip = 0x800 (external interrupt in progress but masked)
*/