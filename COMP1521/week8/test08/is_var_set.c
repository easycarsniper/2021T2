#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

int main (int argc, char *argv[]) {
    char *file = argv[1];
    if (getenv(file) == NULL) {
        printf("0\n");
    } else {
        char *path = getenv(file);
        if (strlen(path) < 1) {
            printf("0\n");
        } else {
            printf("1\n");
        }    
    }
    return 0;
}