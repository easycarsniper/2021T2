// Swap bytes of a short

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

// given uint16_t value return the value with its bytes swapped
uint16_t short_swap(uint16_t value) {
    // PUT YOUR CODE HERE
    uint16_t mask_1 = 0b1111111100000000;
    uint16_t mask_2 = 0b0000000011111111;
    uint16_t result = 0x0000;
    mask_1 = mask_1 & value;
    mask_1 = mask_1 >> 8;
    mask_2 = mask_2 & value;
    mask_2 = mask_2 << 8;
    result = result | mask_1;
    result = result | mask_2;
    return result;
}
