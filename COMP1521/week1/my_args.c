#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Program name: %s\n", argv[0]);
        printf("There are no other arguments\n");
    } else {
        printf("Program name: %s\n", argv[0]);
        printf("There are %d arguments:\n", argc - 1);
        int count;
        for (count = 1; count < argc; count++) {
            printf("\tArgument %d is \"%s\"\n", count, argv[count]);
        }
    }
    return 0;
}