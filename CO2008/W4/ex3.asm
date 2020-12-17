	.data:
	a: .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
	msg: .asciiz "Enter an integer: "
	msg1: .asciiz "Position of the integer: "
	msg2: .asciiz "The integer does not exist in the array"

	# Start program code
	.text:

	.globl main

main:
	li $s7, 40 	# array size
	li $s1, 0		# int i = 0
	li $s2, 0		# int pos = 0
	la $s3, a
	li $a0, 0

	# Print string msg
	li $v0, 4
	la $a0, msg
	syscall

	# Get input and save
	li $v0, 5
	syscall
	move $s0, $v0

WHILE:
	slt $t0, $s1, $s7	# while (i < n)
	bne $t0, 1, WEXIT

	add $t1, $s1, $s3		# index [i]
	lw $t1, 0($t1)		# get a[i]
	beq $t1, $s0, TRUE
	addi $s1, $s1, 4
	addi $s2, $s2, 1
	j WHILE
WEXIT:
	# Print string msg2
	li      $v0, 4
	la      $a0, msg2
	syscall
j EXIT
TRUE:
	# Print string msg1
	li      $v0, 4
	la      $a0, msg1
	syscall

	# Print pos
	li      $v0, 1
	move    $a0, $s2
	syscall
EXIT:
	# Exit
	li      $v0, 10
	syscall
