#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1], "r");
    int i = 0;
    int c;
    bool isascii = true;
    while ((c = fgetc(fp)) != EOF) {
        if (isascii(c) == 0) {
            isascii = false;
            break;
        }
        i++;
    }
    if (isascii == true) {
        printf("%s is all ASCII\n", argv[1]);
    } else {
        printf("%s: byte %d is non-ASCII\n", argv[1], i);
    }
}