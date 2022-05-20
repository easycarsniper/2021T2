#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("wrong number of arguments\n");
        return 0;
    }
    long i = 0;
    FILE *fp;
    int c;
    
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
      perror("Error in opening file");
      exit(1);
    }
    while ((c = fgetc(fp)) != EOF) {
        printf("byte %4ld: %3d 0x%02x ", i, c, c);
        if (isprint(c) != 0) {
            printf("\'%c\'", c);
        }
        printf("\n");
        i++;
    }
    
    fclose(fp);
    return 0;
}
