  .data:
  msg: .asciiz "Enter an integer: "
  msg1: .ascii "The entered number is not positive, the sum is: "

  # Start program code
  .text:

  .globl main

#	int i = 1, sum = -1;
#	while (i > 0)
#   	{
#		sum += i;
#		cout << "Enter an integer: ";
#		cin >> i;
#	}
#	cout << "The entered number is not positive, the sum is: " << sum;


main:
	# i : s0, sum : s1
	addi	$s0, $zero, 1 	# int i = 1
	addi	$s1, $zero, -1 	# int sum = -1

WHILE:
	slt		$t0, $zero, $s0	# while (i > 0)
	bne		$t0, 1, WEXIT

	add		$s1, $s1, $s0 	# sum += i
	li		$v0, 4					# cout << "Enter an integer: "
  la		$a0, msg				#
	syscall								#
  li		$v0, 5				# cin >> i
  syscall								#
  move	$s0, $v0			#

	j WHILE

WEXIT:
	# Print string msg1
	li		$v0, 4
	la		$a0, msg1
	syscall

	# Print sum
	li		$v0, 1
	move	$a0, $s1
	syscall

	# Exit
	li		$v0, 10
	syscall
