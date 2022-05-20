// Multiply a float by 2048 using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -inf, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//
uint32_t float_2048(uint32_t f) {
    // PUT YOUR CODE HERE
    uint32_t f_exp = f >> 23 & 0xff;
    uint32_t f_sign = f >> 31;
    //uint32_t f_frac = f & 0b11111111111111111111111;
    uint32_t mask = 0b10000000011111111111111111111111;
    uint32_t result_exp = f_exp + 11;
    uint32_t result = 0;
    uint32_t neg_zero = 0b10000000000000000000000000000000; 
    if (f_exp == 0xff || f == 0 || f == neg_zero) {
        return f;
    }
    if (result_exp < 0xff) {
        result = f & mask;
        result_exp = result_exp << 23;
        result = result | result_exp;
        return result;
    } else {
        result = f_sign << 31;
        result = result | 0b01111111100000000000000000000000;
        return result;
    }
}
