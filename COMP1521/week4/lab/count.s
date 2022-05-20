# read a number n and print the integers 1..n one per line

main:                 # int main(void)
    la   $a0, prompt  # printf("Enter a number: ");
    li   $v0, 4
    syscall

    li   $v0, 5       # scanf("%d", number);
    syscall
    move $t0, $v0

    li $t1, 1          # set a varable to 1
loop:
    bgt $t1, $t0, end   # if (t1 > t0) goto end;
    move  $a0, $t1      # printf("%d", t1);
    li   $v0, 1
    syscall
    addi $t1, 1        # t1++;

    li   $a0, '\n'    # printf("%c", '\n');
    li   $v0, 11
    syscall

    j loop            # goto loop;

end:
    li $v0 0
    jr   $ra          # return

    .data
prompt:
    .asciiz "Enter a number: "
