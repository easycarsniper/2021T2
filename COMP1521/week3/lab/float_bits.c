// Extract the 3 parts of a float using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// separate out the 3 components of a float
float_components_t float_bits(uint32_t f) {
    // PUT YOUR CODE HERE
    struct float_components *new_float = malloc(sizeof(struct float_components));
    uint32_t exponent_mask = 0b11111111;
    uint32_t fraction_mask = 0b11111111111111111111111;

    new_float->sign = f >> 31; 
    new_float->exponent = f >> 23 & exponent_mask;
    new_float->fraction = f & fraction_mask; 
    return *new_float;
}

// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f) {
    // PUT YOUR CODE HERE
    if (f.exponent == 0xff && f.fraction != 0) {
        return 1;
    } else {
        return 0;
    }
}

// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f) {
    // PUT YOUR CODE HERE
    if (f.exponent == 0xff && f.sign == 0 && f.fraction == 0) {
        return 1;
    } else {
        return 0;
    }
}

// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f) {
    // PUT YOUR CODE HERE
    if (f.exponent == 0xff && f.sign == 1 && f.fraction == 0) {
        return 1;
    } else {
        return 0;
    } 
}

// given the 3 components of a float
// return 1 if it is 0 or -0, 0 otherwise
int is_zero(float_components_t f) {
    // PUT YOUR CODE HERE
    if (f.fraction == 0 && f.exponent == 0b00000000) {
        return 1;
    } else {
        return 0;
    }
}
