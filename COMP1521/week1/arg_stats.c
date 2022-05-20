#include <stdio.h>
#include <stdlib.h>

int find_min(int argc, char *argv[]);
int find_max(int argc, char *argv[]);
int find_sum(int argc, char *argv[]);
int find_prod(int argc,char *argv[]);

int main (int argc, char *argv[]) {
    int min, max, sum, prod, mean;
    min = find_min(argc, argv);
    max = find_max(argc, argv);
    sum = find_sum(argc, argv);
    prod = find_prod(argc, argv);
    mean = sum / (argc -1);
    printf("MIN:  %d\n", min);
    printf("MAX:  %d\n", max);
    printf("SUM:  %d\n", sum);
    printf("PROD: %d\n", prod);
    printf("MEAN: %d\n", mean);
    return 0;
}

int find_min(int argc, char *argv[]) {
    int i = 1;
    long int min = atol(argv[i]);
    for (i = 1; i < argc; i++) {
        if (min > atol(argv[i]) ) {
            long int num = atol(argv[i]);
            min = num;
        }
    }
    return min;
}

int find_max(int argc, char *argv[]) {
    int i = 0;
    int max = 0;   
    for (i = 0; i < argc; i++) {
        if (max < atol(argv[i]) ) {
            long int num = atol(argv[i]);
            max = num;
        }
    }
    return max;
}

int find_sum(int argc, char *argv[]) {
    int sum = 0;
    int i = 0;
    for (i = 0; i < argc; i++) {
        long int num = atol(argv[i]);
        sum += num;
    }
    return sum;
}

int find_prod(int argc,char *argv[]) {
    int prod = 1;
    int i = 1;
    for (i = 1; i < argc; i++) {
        int num = atol(argv[i]);
        prod = prod * num;
    }
    return prod;
}