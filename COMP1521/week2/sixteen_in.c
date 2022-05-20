// Convert string of binary digits to 16-bit signed integer

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define N_BITS 16

int16_t sixteen_in(char *bits);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        printf("%d\n", sixteen_in(argv[arg]));
    }

    return 0;
}

//
// given a string of binary digits ('1' and '0')
// return the corresponding signed 16 bit integer
//
int16_t sixteen_in(char *bits) {

    // PUT YOUR CODE HERE
    int16_t num = 0;
    int16_t tem_num = 0;
    int i;
    for (i = 0; i < N_BITS; i++) {
        if (bits[i] == '1') {
            tem_num = 0;
            tem_num = tem_num | 1;
            tem_num = tem_num << (N_BITS - i - 1); 
            num = num | tem_num;
        } 
    }
    return num;
}

