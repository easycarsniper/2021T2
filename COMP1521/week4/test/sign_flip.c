#include "sign_flip.h"

// given the 32 bits of a float return it with its sign flipped
uint32_t sign_flip(uint32_t f) {
    uint32_t sign = f >> 31;
    uint32_t result = 0;
    if (sign == 0) {
        // if sign is +ve
        sign = 1;
        sign = sign << 31;
        result = f | sign;
    } else {
        // if sign is -ve
        result = f << 1;
        result = result >> 1;
    }
    return result; // REPLACE ME WITH YOUR CODE
}
