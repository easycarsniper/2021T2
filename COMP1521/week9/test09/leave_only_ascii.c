#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1], "r");
    int i = 0;
    int c;
    char temp[100000];
    while(1) {
        c = fgetc(fp);
        if (c == EOF) {
            break;
        }
        if (isascii(c) && c < 128) {
            temp[i] = c;
            i++;
        }
    }
    FILE *fp2 = fopen(argv[1], "w");
    i = 0;
    while (temp[i] != '\n') {
        fputc(temp[i], fp2);
        i++;
    }
    fputc(temp[i], fp2);
}