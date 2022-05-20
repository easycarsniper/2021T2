#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char *value = getenv("HOME");
    char *name = "/.diary";
    strcat(value, name);   
    FILE *fp = fopen(value, "a");
    for (int i = 1; i < argc; i++) {
        fputs(argv[i], fp);
        fputc(' ', fp);
    }
    fputc('\n', fp);
    return 0;
}