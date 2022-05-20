#include <stdio.h>
#include <sys/stat.h>

int main (int argc, char *argv[]) {
    struct stat sb;
    int fd = stat(argv[1], &sb);
    if (fd == 0) {
        if (S_ISDIR(sb.st_mode) == 0) {
            printf("0\n");
        } else {
            printf("1\n");
        }
    } else {
        printf("0\n");
    }
    return 0;
}