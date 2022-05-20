# read a line and print whether it is a palindrom

main:
    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line
    la   $a1, 256
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #

    li $t0, 0   #int i = 0    
loop0:  
    lb $a0, line($t0)
    beqz	$a0, end0	# if $t1 == 0 then end
    addi $t0, 1
    j loop0
end0:
    li $t1, 0   #    int j = 0;
    addi $t0, -2    # int k = i - 2;
loop1:
    bge		$t1, $t0, end1	# if $t1 <= $t0 then end1
    lb $t2, line($t1)   # line[j]
    lb $t3, line($t0)   # line[k]
    beq		$t2, $t3, else	# if $t2 == $t1 then target
    
    la   $a0, not_palindrome    # printf("not palindrome\n");
    li   $v0, 4
    syscall
    j exit

else:
    addi $t1, 1
    addi $t0, -1
    j loop1
end1:

    la   $a0, palindrome
    li   $v0, 4
    syscall

exit:
    li   $v0, 0          # return 0
    jr   $ra


.data
str0:
    .asciiz "Enter a line of input: "
palindrome:
    .asciiz "palindrome\n"
not_palindrome:
    .asciiz "not palindrome\n"


# line of input stored here
line:
    .space 256

