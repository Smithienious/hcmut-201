    .data
      nums: .word 10
      elems: .word 1 0 2 9 3 8 4 7 5 6

    .text
      addi  $t9, $zero, 1       # 1
      la    $s0, elems          # Address of element at index i
      addi  $s1, $s0, 4         # Address of element at index i + 1
      add   $s2, $zero, $zero   # Index i
      addi  $s3, $s2, 1         # Index i + 1
      la    $t7, nums           # Limiter base address
      lw    $s7, 0($t7)         # Limiter

  Sort:
      beq   $t9, $s7, Exit

      lw    $t0, 0($s0)
      lw    $t1, 0($s1)

      slt   $t2, $t0, $t1
      beq   $t2, $t9, NoSwap
      sw    $t0, 0($s1)
      sw    $t1, 0($s0)

  NoSwap:
      addi  $s0, $s0, 4
      addi  $s1, $s0, 4
      addi  $s2, $s2, 1
      addi  $s3, $s2, 1

      bne   $s3, $s7, NotEnd
      la    $s0, elems
      addi  $s1, $s0, 4
      add   $s2, $zero, $zero
      addi  $s3, $s2, 1
      addi  $s7, $s7, -1

  NotEnd:
      j Sort

  Exit:
      la    $s0, elems
      add   $s2, $zero, $zero
      la    $t7, nums
      lw    $s7, 0($t7)

  Print:
      beq   $s2, $s7, SPrint
      lw    $s1, 0($s0)

      # Print sum
      li    $v0, 1
      move  $a0, $s1
      syscall

      addi  $s0, $s0, 4
      addi  $s2, $s2, 1
      j Print

  SPrint:
      # Exit
      li      $v0, 10
      syscall
