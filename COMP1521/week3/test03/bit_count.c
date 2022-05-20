// count bits in a uint64_t

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// return how many 1 bits value contains
int bit_count(uint64_t value) {
    // PUT YOUR CODE HERE
    int i = 0;
    uint64_t mask = 1;
    int count = 0;
    for(i = 0; i <= 63; i++) {
        uint64_t tem_value = value;
        tem_value = value >> i;
        mask = mask & tem_value;
        if (mask != 0) {
            count++;
        }
        mask = 1;
    }
    return count;
}
