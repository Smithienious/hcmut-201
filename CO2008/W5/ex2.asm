    .data:
    msg: .asciiz "Enter an integer: "
    print: .asciiz "a = "
    break: .asciiz "Please input other integer numbers"

    # Start program code
    .text:

    .globl main
main:
    addi    $s1, $zero, 10         # b = 10
    addi    $s2, $zero, 5          # c = 5

    # Print string msg
    li      $v0, 4
    la      $a0, msg
    syscall

    # Get input and save
    li      $v0, 5
    syscall
    move    $s0, $v0

    add     $t0, $s1, $s2           # b + c
    sub     $t1, $s1, $s2           # b - c
    sub     $t2, $s2, $s1           # c - b

    beq     $s0, $t0, case0
    beq     $s0, $t1, case1
    beq     $s0, $t2, case2
    j default

case0:
    # Print string print
    li      $v0, 4
    la      $a0, print
    syscall

    # Print a
    li      $v0, 1
    move    $a0, $s0
    syscall

    j Exit

case1:
    # Print string print
    li      $v0, 4
    la      $a0, print
    syscall

    # Print a
    li      $v0, 1
    move    $a0, $s0
    syscall

    j Exit

case2:
    # Print string print
    li      $v0, 4
    la      $a0, print
    syscall

    # Print a
    li      $v0, 1
    move    $a0, $s0
    syscall

    j Exit

default:
    # Print string break
    li      $v0, 4
    la      $a0, break
    syscall

Exit:
    # Exit
    li      $v0, 10
    syscall
