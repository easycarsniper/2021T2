# read a line and print its length

main:
    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line
    la   $a1, 256
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #

    la   $a0, str1       # printf("Line length: ");
    li   $v0, 4
    syscall

    li $t0, 0   #int i = 0    
loop0:  
    lb $t1, line($t0)
    beqz	$t1, end0	# if $t1 == 0 then end
    addi $t0, 1
    j loop0
end0:

    move   $a0, $t0        # printf("%d", i);
    li   $v0, 1
    syscall

    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0          # return 0
    jr   $ra


.data
str0:
    .asciiz "Enter a line of input: "
str1:
    .asciiz "Line length: "


# line of input stored here
line:
    .space 256

