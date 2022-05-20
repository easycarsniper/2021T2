#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "r");
    int i = 0;
    int c1, c2;
    while (1) {
        c1 = fgetc(fp);
        c2 = fgetc(fp2);
        if (c1 == EOF && c2 == EOF) {
            printf("Files are identical\n");
            break;
        }
        if (c1 == EOF) {
            printf("EOF on %s\n", argv[1]);
            break;
        }
        if (c2 == EOF) {
            printf("EOF on %s\n", argv[2]);
            break;
        }
        if (c1 != c2) {
            printf("Files differ at byte %d\n", i);
            break;
        }
        i++;
    }
}