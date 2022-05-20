# Read a number and print positive multiples of 7 or 11 < n

main:                  # int main(void) {

    la   $a0, prompt   # printf("Enter a number: ");
    li   $v0, 4
    syscall

    li   $v0, 5         # scanf("%d", number);
    syscall
    move $t0, $v0

    li $t1, 1           # int i = 1;
loop:
    bge $t1, $t0, end
    move $t2, $t1
    rem $t2, $t2, 7     # if(x & 7 == 0)
    beq $t2, 0, print

    move $t2, $t1
    rem $t2, $t2, 11    # if (x & 11 == 0)
    beq $t2, 0, print

    addi $t1, 1    
    j loop

print:
    move $a0, $t1        #   printf("%d", t1);
    li   $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall
    addi $t1, 1
    j loop

end:
    jr   $ra           # return

    .data
prompt:
    .asciiz "Enter a number: "
