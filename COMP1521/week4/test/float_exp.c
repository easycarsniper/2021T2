#include "float_exp.h"

// given the 32 bits of a float return the exponent
uint32_t float_exp(uint32_t f) {
    f = f << 1;
    f = f >> 24;
    return f; // REPLACE ME WITH YOUR CODE
}