main:
    li   $v0, 5         #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li   $v0, 5         #   scanf("%d", &y);
    syscall             #
    move $t1, $v0

    addi $t0, $t0, 1  # int i = x + 1

loop:
    bge		$t0, $t1, end	# if $t0 >= $t1 then goto target
    
    beq		$t0, 13, break0	# if $t0 == 13 then goto break
    
    move   $a0, $t0        #   printf("%d\n", i);
    li   $v0, 1
    syscall
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

break0:
    addi $t0, $t0, 1
    j loop

end:

    li   $v0, 0         # return 0
    jr   $ra
