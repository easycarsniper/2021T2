#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    int num = atol(argv[1]);
    while (num != 1) {
        printf("%d\n", num);
        if (num % 2 == 0) {
            num = num / 2;
        } else {
            num = (3 * num) + 1;
        }
    }
    printf("%d\n", num);
    
    return 0;
}