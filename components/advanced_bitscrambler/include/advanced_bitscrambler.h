// Designed and programed by Srdjan Crnjanski 2026 V1.0
// all rights reserved
// you can use the code for free, but author name, year, version and all comments must be preserved within
// your source files

#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// following bitwise functions are sorted by their natural ID (result of truth table interpretted as 4 bit number)
// order MUST NOT be changed!
// Names A and B are generic names from two bits truth tables usualy contain labels as input A and input B
// and has nothing to do with Alpha and Blue channels (coincidence in names with generic names) 

typedef enum {
 BITWISE_CONST_LOW = 0,     // constant LOW independent of A and B, always produce low level
 BITWISE_A_NOR_B,           // ~(A | B)
 BITWISE_NOT_A_AND_B,       // ~A & B
 BITWISE_NOT_A,             // ~A       this function is only A dependant regardless of B state (inverted A)
 BITWISE_A_AND_NOT_B,       //  A & ~B
 BITWISE_NOT_B,             // ~B       this function is only B dependent regardless of A state (inverted B)
 BITWISE_A_XOR_B,           //  A ^ B   standard exclusive or 
 BITWISE_A_NAND_B,          // ~(A & B)
 BITWISE_A_AND_B,           // A & B
 BITWISE_A_NXOR_B,          // ~(A ^ B) inverted exclusive or
 BITWISE_B,                 // B        this function is only B dependent (B buffer)
 BITWISE_NOT_A_OR_B,        // ~A | B
 BITWISE_A,                 // A        this function is only A dependent (A buffer) 
 BITWISE_A_OR_NOT_B,        // A | ~B
 BITWISE_A_OR_B,            // A | B
 BITWISE_CONST_HIGH         // constant HIGH independent of A and B always produce high level
} bitscrambler_bitwise_function_t;

// this is alu bitwise sim
// bitscrabler is coded to take Blue channel as A input, Grenn channel as B input and function 4 bit ID is stored in Alpha channel
// since it is per pixel, it means that ie Alpha channel can contain different BITWISE opperation ID for each pixel
// assembler code can be modified that Red and Blue or Red and Green are used for bitwise operations
// also function ID can be codded into any other channel if Alpha is required as bitwise opperand
extern const uint8_t advanced_alu_sim_bga[]  asm("_binary_bitscrambler_program_advanced_alu_sim_bga_start");

// simplified versions of bitscrabler initialization just for demonstration purpose
void init_bitscrambler(void);  
void deinit_bitscrambler(void);
size_t run_bitscrambler(void* in_buffer, uint32_t in_size_bytes, void* out_buffer, uint32_t out_size_bytes, const void *program_bin);

#ifdef __cplusplus
}
#endif