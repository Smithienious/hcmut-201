    .data:
    X: .space 40 # Reserve 40 bytes
    msg1: .asciiz "Enter an integer: "
    msg2: .asciiz "The sum of all elements is "

    # Start program code
    .text:

    .globl main
main:
    la      $s7, X              # Address of X
    add     $s0, $zero, $zero   # Counter
    add     $s1, $zero, $zero   # Sum
    addi    $t7, $zero, 40      # Limiter
Input:
    add     $t0, $s0, $s7       # Address of element

    # Print string msg1
    li      $v0, 4
    la      $a0, msg1
    syscall

    # Get input and save
    li      $v0, 5
    syscall
    move    $t1, $v0

    sw      $t1, 0($t0)
    addi    $s0, $s0, 4         # i = i + 1
    beq     $s0, $t7, IExit
    j       Input

IExit:
    add     $s0, $zero, $zero   # Counter
    add     $s1, $zero, $zero   # Sum
Sum:
    add     $t0, $s0, $s7       # Address of element
    lw      $t1, 0($t0)
    add     $s1, $s1, $t1       # Summer
    addi    $s0, $s0, 4         # i = i + 1
    beq     $s0, $t7, SExit
    j       Sum

SExit:
    # Print string msg2
    li      $v0, 4
    la      $a0, msg2
    syscall

    # Print sum
    li      $v0, 1
    move    $a0, $s1
    syscall

    # Exit
    li      $v0, 10
    syscall
