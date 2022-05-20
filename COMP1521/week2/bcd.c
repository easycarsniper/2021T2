#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int bcd(int bcd_value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= 0x0909);
        int bcd_value = l;

        printf("%d\n", bcd(bcd_value));
    }

    return 0;
}

// given a  BCD encoded value between 0 .. 99
// return corresponding integer
int bcd(int bcd_value) {

    // PUT YOUR CODE HERE
    int result = 0;
    int multi = 1;
    uint16_t test = 15;
    int i = 0;

    while (bcd_value != 0) {
        
        test = 15;
        test = test & bcd_value; // get the first 4 digit in bcd
        result += (test * multi); //result = the value of that 4 digit times multiple(1, 10, 100,etc)
        bcd_value = bcd_value >> 4; //move 4 digit for every iteration
        //printf("i = %d bcd=%d, result = result + %d time %d = %d\n",i, bcd_value, test, multi, result);
        if (test != 0 || i % 2 == 0) {
            multi = multi * 10; //increase it by 10 for every iteration
        }
        
        i++;
    }

    return result;
}

