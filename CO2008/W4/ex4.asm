	.data:
	a: .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
	msg: .asciiz "Enter an integer: "
	msg1: .asciiz "New array is: "
	msg2: .asciiz " "
	msg3: .asciiz "Not possible"

	# Start program code
	.text:

	.globl main

main:
	li $s7, 40 	# array size
	li $s1, 0	#int i = 0
	la $s2, a
	li $a0, 0

	# Print string msg
	li      $v0, 4
	la      $a0, msg
	syscall

	# Get input and save
	li      $v0, 5
	syscall
	move    $s0, $v0

	li $t1, 9
	slt $t0, $s0, $t1
	beq $t0, 0, NOTPOSSIBLE

	move $a0, $s2
	move $a1, $s0
	jal SWAP

	# Print string msg1
	li      $v0, 4
	la      $a0, msg1
	syscall
WHILE:
	slt $t0, $s1, $s7	# while (i < n)
	bne $t0, 1, WEXIT

	add $t1, $s1, $s2	# index [i]
	lw $t1, 0($t1)		# get a[i]

	# Print a[i]
	li      $v0, 1
	move    $a0, $t1
	syscall
	# Print string msg2
	li      $v0, 4
	la      $a0, msg2
	syscall

	addi $s1, $s1, 4
	j WHILE
WEXIT:
	j EXIT

NOTPOSSIBLE:
	# Print string msg3
	li      $v0, 4
	la      $a0, msg3
	syscall
	EXIT:
	# Exit
	li      $v0, 10
	syscall

SWAP:
	addi $sp, $sp, -4
	sw $s0, 0($sp)

	add $a1, $a1, $a1
	add $a1, $a1, $a1
	add $t0, $a0, $a1
	lw $s0, 0($t0)
	lw $t1, 4($t0)
	sw $t1, 0($t0)
	sw $s0, 4($t0)
	jr $ra

	lw $s0, 0($sp)
	addi $sp, $sp, 4
