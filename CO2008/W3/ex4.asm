    .data:
    X: .word 0, 11, 22, 33, 44, 55, 66, 77, 88, 99
    msg1: .asciiz "Enter an integer between 0 and 10: "
    msg2: .asciiz "Data at index is "

    # Start program code
    .text:

    .globl main
main:
    la      $s7, X              # Address of X
    add     $s0, $zero, $zero   # Counter
    addi    $t6, $zero, 4       # Sum limiter
    addi    $t7, $zero, 40      # Limiter

    # Print string msg1
    li      $v0, 4
    la      $a0, msg1
    syscall

    # Get input and save
    li      $v0, 5
    syscall
    move    $t1, $v0
    mul     $t6, $t1, $t6

Search:
    add     $t0, $s0, $s7       # Address of element
    lw      $t1, 0($t0)
    beq     $s0, $t6, SExit
    beq     $s0, $t7, SExit
    addi    $s0, $s0, 4         # i = i + 1
    j       Search

SExit:
    # Print string msg2
    li      $v0, 4
    la      $a0, msg2
    syscall

    # Print sum
    li      $v0, 1
    move    $a0, $t1
    syscall

    # Exit
    li      $v0, 10
    syscall
