#include <stdio.h>

#define LARGEST_NUM 46

void fibonacci(int num_1, int num_2, int n);

int main () {
    int num_1 = 0;
    int num_2 = 1;
    int check;
    while(scanf("%d", &check) != EOF) {
        fibonacci(num_1, num_2, check);
    }
    
    return 0;
}

void fibonacci(int num_1, int num_2, int n) {
    if (num_1 > LARGEST_NUM || n == 0) {
        printf("%d\n", num_1);
        return;
    } else {
        //printf("%d\n", num_1);
        int new_num = num_1 + num_2;
        num_1 = num_2;
        num_2 = new_num;
        n--;        
        fibonacci(num_1, num_2, n);
    }
}