main:
    li   $v0, 5         #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li $t1, 0  # int i = 0;

loop:
    bge		$t1, $t0, end	# if $t1 >= $t0 then end
    li $t2, 0  #int j = 0

loop2:
    bge		$t2, $t0, end1	# if $t2 >= $t0 then end1

    li   $a0, '*'        #   printf("%d\n", *);
    li   $v0, 11
    syscall
    
    addi $t2, 1 # j++
    j loop2

end1:
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall
    
    addi $t1, 1 # i++
    j loop

end:

    li   $v0, 0         # return 0
    jr   $ra
