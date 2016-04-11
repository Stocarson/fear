#include <stdio.h>
#include "sbox0_definition.h"
#include "print_table.h"

int is_linear_relation_true(int input_bits, int output_bits, int sbox_input, int sbox_output) {

    int i,input_relation_value=0,output_relation_value=0,mask;
    /* compute input relation value */
    for (i=0; i<SBOX_INPUT_BITS; i++) {
        mask=1<<i;
        if (input_bits & mask) {
            input_relation_value ^= (sbox_input & mask)>>i;
        }
    }
    /* compute output relation value */
    for (i=0; i<SBOX_OUTPUT_BITS; i++) {
        mask=1<<i;
        if (output_bits & mask) {
            output_relation_value ^= (sbox_output & mask)>>i;
        }
    }
    /* check if they match, and return accordingly */
    if (input_relation_value==output_relation_value) {
        return 1;
    }
    else
        return 0;
}

int main (int argc, char* argv[]) {
    validate_args(argc, argv);
    int input_relation_bits, output_relation_bits, sbox_input;
    int linear_bias_table[SBOX_INPUT_SIZE][SBOX_OUTPUT_SIZE]= {{0}};
    /* compute how many times the linear relations hold for all the possible sbox inputs */
    for (input_relation_bits=0; input_relation_bits<(SBOX_INPUT_SIZE); input_relation_bits++) {
        for (output_relation_bits=0; output_relation_bits<SBOX_OUTPUT_SIZE; output_relation_bits++) {
            for(sbox_input=0; sbox_input<SBOX_INPUT_SIZE; sbox_input++) {
                linear_bias_table[input_relation_bits][output_relation_bits] += is_linear_relation_true(input_relation_bits, output_relation_bits, sbox_input, sbox(sbox_input) );
            }
        }
    }
    /* subtract the 1/2 from the bias table */
    for (input_relation_bits=0; input_relation_bits<(SBOX_INPUT_SIZE); input_relation_bits++) {
        for (output_relation_bits=0; output_relation_bits<SBOX_OUTPUT_SIZE; output_relation_bits++) {
            linear_bias_table[input_relation_bits][output_relation_bits] -= ((SBOX_OUTPUT_SIZE)/2);
        }
    }
    pretty_print(linear_bias_table,argc,argv);
}
