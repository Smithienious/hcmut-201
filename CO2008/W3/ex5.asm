    .data:
    X: .space 40
    Y: .space 40
    msg1: .asciiz "Enter an integer: "
    msg2: .ascii " "

    # Start program code
    .text:

    .globl main
main:
    la   $s7, X # Address of X
    la   $s6, Y
    add  $s0, $zero, $zero # Counter
    add  $s1, $zero, $zero # Sum
    addi $t7, $zero, 40 # Limiter
Input:
    add  $t0, $s0, $s7 # Address of element

    # Print string msg1
    li   $v0, 4
    la   $a0, msg1
    syscall

    # Get input and save
    li   $v0, 5
    syscall
    move $t1, $v0

    sw   $t1, 0($t0)
    addi $s0, $s0, 4 # i = i + 1
    beq  $s0, $t7, IExit
    j    Input

IExit:
    addi $s0, $t7, -4 # Counter
    addi $s5, $zero, -4
    addi $t6, $zero, 36
Copy:
    add  $t0, $s0, $s7 # Address of element
    lw   $t1, 0($t0)
    addi $s0, $s0, -4 # i = i + 1
    li   $v0, 1 # print_int syscall code = 1
    sub  $t2, $t6, $s0
    add  $t2, $t2, $s6
    sw $t1, 0($st2)
    beq $s0, $s5, CExit
    j Copy

CExit:
    addi $s0, $zero, 0
    li $v0, 10
    syscall
