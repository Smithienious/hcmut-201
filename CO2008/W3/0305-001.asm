	.data
	arr: .word 34, 23, 15, 82, 38, 56, 48, 93, 49, 11
	newarr: .word 0:10
	msg: .asciiz "Hello World"
	space: .asciiz " "
	endl: .asciiz "\n"

	.text

	.globl main

main:
	
	la $s0, arr
	
	add $s1, $zero, $zero
	
	
L1:
	lw $t1, 0($s0)
	li	$v0,1		
	move	$a0, $t1	
	syscall
	
	addi $s0, $s0, 4
	addi $s1, $s1, 1
	
	li	$v0, 4		
	la	$a0, space	
	syscall
	
	beq $s1, 10, r1
	j L1

r1:
	li	$v0, 4		
	la	$a0, endl
	la $s3, newarr	
	syscall
	addi $s0, $s0, -4
	
rev:
	lw $t2, 0($s0)
	sw $t2, 0($s3)
	addi $s0, $s0, -4
	addi $s3, $s3, 4
	addi $s1, $s1, -1
	
	beq $s1, 0, print
	j rev
	
print:
	la $s3, newarr
	addi $s1, $zero, 0
	j print2
	
print2:
	lw $t1, 0($s3)
	li	$v0,1		
	move	$a0, $t1	
	syscall
	
	addi $s3, $s3, 4
	addi $s1, $s1, 1
	
	li	$v0, 4		
	la	$a0, space	
	syscall
	
	beq $s1, 10, Exit
	j print2

Exit:
	li $v0, 10
	syscall
	
	
