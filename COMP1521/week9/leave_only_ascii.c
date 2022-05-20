#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1], "r+");
    int i = 0;
    int c;
    char *temp;
    while(1) {
        c = fgetc(fp);
        if (c == EOF) {
            break;
        }
        if (c < 128) {
            temp[i] = c;
            i++;
        }
    }
    fwrite(temp, 1, sizeof(temp), fp);
}