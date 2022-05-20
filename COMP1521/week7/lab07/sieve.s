# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
main:
    # PUT YOUR CODE
    li $t0, 0   # int i = 0
loop0:
    bge $t0, 1000, end0  # while (t0 < 1000)
    li $t2, 1
    sb $t2, prime($t0)      # prime[t0] = 1;
    addi $t0, $t0, 1        # t0++;
    j loop0
end0:
    li $t0, 2
loop1:
    bge $t0, 1000, end1     # while (t0 < 1000)
    lb $t2, prime($t0)      
    beqz $t2, endif         # if (prime[t0])

    move $a0, $t0  # printf("%d", t0);
    li $v0, 1
    syscall

    li   $a0, '\n'     # printf("%c", '\n');
    li   $v0, 11
    syscall

    mul $t1, $t0, 2    # int t1 = 2 * t0;

loop2:
    bge $t1, 1000, end2    # while (t1 < 1000)
    li $t3, 0   
    sb $t3, prime($t1)      # prime[t1] = 0;

    add $t1, $t1, $t0   # j = j + i;
    j loop2
end2:

endif:
    addi $t0, $t0, 1
    j loop1
end1:

    li $v0, 0           # return 0
    jr $31

.data
prime:
    .space 1000