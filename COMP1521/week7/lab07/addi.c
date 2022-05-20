// generate the opcode for an addi instruction

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "addi.h"

// return the MIPS opcode for addi $t,$s, i
uint32_t addi(int t, int s, int i) {
    //001000ssssstttttIIIIIIIIIIIIIIII
    uint32_t result = 0;
    int addi = 0b001000;
    addi = addi << 26;
    int rt = t;
    rt = rt << 16;
    int rs = s;
    rs = rs << 21;
    uint16_t I = i;
    result = result | addi | rt | rs | I;

    return result; // REPLACE WITH YOUR CODE

}
