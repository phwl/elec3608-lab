/**
 * @brief Test program MTVEC read
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
    csrrw x1, mtvec, x0;    /* Read MTVEC register into X1.  No write due to zero bits of x0 */
    ebreak

/* expected result:
    expect h0:x0 = 0x0
    expect h0:x1 = 0x1000 (mtvec)
*/