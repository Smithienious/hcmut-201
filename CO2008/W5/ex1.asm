  # Start program code
  .text:

  .globl main
main:
	# Multiplication
	lui		$t0, 0x1000
	li		$t1, 4				# sll 2
	mult	$t0, $t1
	mflo	$s0
	mfhi	$s1

	# Division
	li		$t0, 10
	li		$t1, 7
	div		$t0, $t1
	mflo	$s0
	mfhi	$s1

	# Exit
	li		$v0, 10
	syscall
