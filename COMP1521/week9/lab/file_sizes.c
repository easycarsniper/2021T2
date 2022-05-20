#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


long long stat_size(char *pathname);
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wrong number of arguments\n");
        return 0;
    }
    long long total = 0;
    for (int i = 1; i < argc; i++) {
        total += stat_size(argv[i]);
    }
    printf("Total: %lld bytes\n", total);
    return 0;
}

long long stat_size(char *pathname) {
    printf("%s: ", pathname);
    struct stat s;
    if (stat(pathname, &s) != 0) {
        perror(pathname);
        exit(1);
    }
    printf("%ld bytes\n", s.st_size);
    return s.st_size;
}
