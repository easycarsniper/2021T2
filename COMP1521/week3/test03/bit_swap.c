// swap pairs of bits of a 64-bit value, using bitwise operators

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include <stdio.h>

// return value with pairs of bits swapped
uint64_t swap(uint64_t value, uint64_t mask_1, uint64_t mask_2);

uint64_t bit_swap(uint64_t value) {
    // PUT YOUR CODE HERE
    uint64_t mask_1 = 1;
    uint64_t mask_2 = 2;
    uint64_t tem_value = 0;
    uint64_t result = 0;
    uint64_t swap_result = 0;
    int i = 0;
    for (i = 0; i < 64 ; i = i + 2) {
        tem_value = value;
        tem_value = tem_value >> i;
        swap_result = swap(tem_value, mask_1, mask_2);
        swap_result = swap_result << i;
        result = result | swap_result;
    }
    return result;
}

uint64_t swap(uint64_t value, uint64_t mask_1, uint64_t mask_2) {
    uint64_t s_value = 0;
    mask_1 = mask_1 & value;
    mask_2 = mask_2 & value;
    mask_1 = mask_1 << 1;
    mask_2 = mask_2 >> 1;
    s_value = s_value | mask_1;
    s_value = s_value | mask_2;
    return s_value;
}