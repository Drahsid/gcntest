.set noreorder

.section .text

.global entrypoint
entrypoint:
    la      $t2, entrypoint_main
    la      $sp, gStackBoot
    la      $t0, __bss_start
    la      $t1, __bss_size
    la      $t3, gStackSizeBoot
    lw      $t3, 0x0($t3)
.LwipeBss:
    sw      $zero, 0x0($t0)
    addi    $t1, $t1, -4
    bnez    $t1, .LwipeBss
    addi    $t0, $t0, 4
    jr      $t2
    addu    $sp, $sp, $t3
    nop

