#include "bit_rotate.h"

// return the value bits rotated left n_rotations
uint16_t bit_rotate(int n_rotations, uint16_t bits) {
    int i = 0;
    if (n_rotations > 0) {
        // if n_rotations is +ve, shift left
        for(i = 0; i < n_rotations; i++) {
            //shift one bit for n times
            uint16_t mask = 0;
            mask = bits >> 15; // get the first bits
            bits = bits << 1; // push bits left 1
            bits = bits | mask;
        }
    } else {
        // n_rotations is =ve, shift right
        for (i = 0; i > n_rotations; i--) {
            // shift right one bit
            uint16_t mask = 1;
            mask = mask & bits;
            mask = mask << 15;
            bits = bits >> 1;
            bits = bits | mask;
        }
    }

    return bits; //REPLACE ME WITH YOUR CODE
}
