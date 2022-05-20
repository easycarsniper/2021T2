#include <stdio.h>
#include <string.h>

#define MAX_NUM 1024

int main () {
    char str[MAX_NUM]; 
    int str_length, check;
    while (scanf("%d", &check) != EOF) {
        fgets(str, MAX_NUM, stdin);
        str_length = strlen(str);
        if (str_length % 2 == 0) {
            fputs(str, stdout);
        }
    }
    
    return 0;
}