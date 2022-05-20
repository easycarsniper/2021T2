#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BCD_DIGITS 8

uint32_t packed_bcd(uint32_t packed_bcd);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= UINT32_MAX);
        uint32_t packed_bcd_value = l;

        printf("%lu\n", (unsigned long)packed_bcd(packed_bcd_value));
    }

    return 0;
}

// given a packed BCD encoded value between 0 .. 99999999
// return the corresponding integer
uint32_t packed_bcd(uint32_t packed_bcd_value) {

    // PUT YOUR CODE HERE
    int result = 0;
    int multi = 1;
    uint16_t test = 15;

    while (packed_bcd_value != 0) {
        
        test = 15;
        test = test & packed_bcd_value; // get the first 4 digit in bcd
        result += (test * multi); //result = the value of that 4 digit times multiple(1, 10, 100,etc)
        packed_bcd_value = packed_bcd_value >> 4; //move 4 digit for every iteration
        multi = multi * 10; //increase it by 10 for every iteration
        
    }
    return result;
}
