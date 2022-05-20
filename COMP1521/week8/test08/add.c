#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "add.h"

// return the MIPS opcode for add $d, $s, $t
uint32_t make_add(uint32_t d, uint32_t s, uint32_t t) {
    //000000ssssstttttddddd00000100000
    uint32_t result = 0;
    int add = 0b000000;
    add = add << 26;
    s = s << 21;
    t = t << 16;
    d = d << 11;
    int reminder = 0b00000100000;
    result = result | s | t | d | reminder;
    return result; 

}
