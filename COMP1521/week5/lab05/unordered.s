# Read 10 numbers into an array
# print 0 if they are in non-decreasing order
# print 1 otherwise

# i in register $t0

main:

    li   $t0, 0         # i = 0
loop0:
    bge  $t0, 10, end0  # while (i < 10) {

    li   $v0, 5         #   scanf("%d", &numbers[i]);
    syscall             #

    mul  $t1, $t0, 4    #   calculate &numbers[i]
    la   $t2, numbers   #
    add  $t3, $t1, $t2  #
    sw   $v0, ($t3)     #   store entered number in array

    addi $t0, $t0, 1    #   i++;
    j    loop0          # }
end0:


    # PUT YOUR CODE HERE
    li $t0, 1 #int i = 1
    li $t1, 0 #int swapped = 0

loop1:
    bge		$t0, 10, end1	# while (i < 10)
    mul $t3, $t0, 4  #   calculate &numbers[i]
    la $t2, numbers
    add $t4, $t3, $t2
    addi $t8, $t3, -4 # t8 = i-1
    add $t7, $t8, $t2
    lw $t5, ($t4)   #t5 = x = numbers[i]
    lw $t6, ($t7) #t6 = y = numbers[i - 1]

    bge		$t5, $t6, break0	# if $t5(x) >= $t6(y) then break
    li $t1, 1

break0:
    addi $t0, $t0, 1
    j loop1

end1:

    move   $a0, $t1        # printf("%d", swapped) swapped = t1
    li   $v0, 1         #
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    jr   $ra

.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};

