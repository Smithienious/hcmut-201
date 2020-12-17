    .data:
    X:      .word 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    msg1:   .asciiz "The sum of all elements of even indexes is "
    msg2:   .asciiz "The sum of all elements of odd indexes is "
    lf:     .asciiz "\n"

    # Start program code
    .text:

    .globl main
main:
    la      $s7, X              # Address of X
    add     $s0, $zero, $zero   # Counter
    add     $s1, $zero, $zero   # Sum of even
    add     $s2, $zero, $zero   # Sum of odd
    addi    $t7, $zero, 40      # Limiter

Sum:
    add     $t0, $s0, $s7       # Address of element
    lw      $t1, 0($t0)
    add     $s1, $s1, $t1       # Even summer
    addi    $s0, $s0, 4         # i = i + 1
    beq     $s0, $t7, SExit

    add     $t0, $s0, $s7       # Address of element
    lw      $t1, 0($t0)
    add     $s2, $s2, $t1       # Odd summer
    addi    $s0, $s0, 4         # i = i + 1
    beq     $s0, $t7, SExit

    j       Sum

SExit:
    # Print string msg1
    li      $v0, 4
    la      $a0, msg1
    syscall

    # Print sum of odd
    li      $v0, 1
    move    $a0, $s1
    syscall

    # Print string new line
    li      $v0, 4
    la      $a0, lf
    syscall

    # Print string msg2
    li      $v0, 4
    la      $a0, msg2
    syscall

    # Print sum of even
    li      $v0, 1
    move    $a0, $s2
    syscall

    # Exit
    li      $v0, 10
    syscall
