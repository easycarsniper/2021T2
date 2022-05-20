// Convert a 16-bit signed integer to a string of binary digits

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BITS 16

char *sixteen_out(int16_t value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= INT16_MIN && l <= INT16_MAX);
        int16_t value = l;

        char *bits = sixteen_out(value);
        printf("%s\n", bits);

        free(bits);
    }

    return 0;
}

// given a signed 16 bit integer
// return a null-terminated string of 16 binary digits ('1' and '0')
// storage for string is allocated using malloc
char *sixteen_out(int16_t value) {

    // PUT YOUR CODE HERE
    char *output = malloc(N_BITS + 1 * sizeof(char));
    int16_t num = 0;
    int16_t tem_num = 1;
    int i = 0;
    int16_t tem_value = value;
    int n = 0;
    
    for (i = 0; i < 16; i++) {
        tem_num = 1;
        tem_num = tem_num & tem_value;
        n = 15 - i;
        if (tem_num == 1) {
            tem_num = tem_num << i;
            num = num | tem_num;
            output[n] = '1';
        } else {
            output[n] = '0';
        } 
        tem_value = tem_value >> 1;     
    }
    output[N_BITS] = '\0';
     
    return output;
}

