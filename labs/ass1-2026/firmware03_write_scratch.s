/**
 * @brief Test program write to the scratch register
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
    addi x1, x0, 0x123;
    csrrw x2, mscratch, x1;  /* read into x2, write from x1 */
    nop;
    csrrw x3, mscratch, x1;  /* read into x3, write from x1 */
    nop;
    ebreak

/* expected result:
    expect h0:x1 = 0x123 (written value)
    expect h0:x2 = 0x0 (old value)
    expect h0:x3 = 0x123 (new readback)
    expect h0:mscratch = 0x123
*/