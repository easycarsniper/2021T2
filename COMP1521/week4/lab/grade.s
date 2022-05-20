# read a mark and print the corresponding UNSW grade

main:
    la   $a0, prompt    # printf("Enter a mark: ");
    li   $v0, 4
    syscall

    li   $v0, 5         # scanf("%d", mark);
    syscall
    move $t0, $v0       # move value in v0 to t0

    blt $t0, 50, Fl
    blt $t0, 65, Ps
    blt $t0, 75, Cr
    blt $t0, 85, Dn
    la   $a0, hd        # printf("HD\n");
    li   $v0, 4
    syscall
    j end

Fl:
    la   $a0, fl        # printf("FL\n");
    li   $v0, 4
    syscall
    j end

Ps:
    la $a0, ps
    li $v0, 4
    syscall
    j end

Cr:
    la $a0, cr
    li $v0, 4
    syscall
    j end

Dn:
    la $a0, dn
    li $v0, 4
    syscall
    j end

end:
    li $v0, 0
    jr   $ra            # return

    .data
prompt:
    .asciiz "Enter a mark: "
fl:
    .asciiz "FL\n"
ps:
    .asciiz "PS\n"
cr:
    .asciiz "CR\n"
dn:
    .asciiz "DN\n"
hd:
    .asciiz "HD\n"
