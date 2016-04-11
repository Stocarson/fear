#include <stdio.h>
#include "sbox_definition.h"
#include "print_table.h"
int is_differential_relation_true(int output_delta, int sbox_output_delta, int sbox_output) {

    /* check if they match, and return accordingly */
    if (output_delta==(sbox_output_delta ^ sbox_output)) {
        return 1;
    }
    else
        return 0;
}
int main (int argc, char* argv[]) {

    validate_args(argc,argv);
    int input_relation_delta, output_relation_delta, sbox_input;
    int differential_bias_table[SBOX_INPUT_SIZE][SBOX_OUTPUT_SIZE]= {{0}};
    /* compute how many times the linear relations hold for all the possible sbox inputs */
    for (input_relation_delta=0; input_relation_delta<(SBOX_INPUT_SIZE); input_relation_delta++) {
        for (output_relation_delta=0; output_relation_delta<SBOX_OUTPUT_SIZE; output_relation_delta++) {
            for(sbox_input=0; sbox_input<SBOX_INPUT_SIZE; sbox_input++) {
                differential_bias_table[input_relation_delta][output_relation_delta] += is_differential_relation_true( output_relation_delta, sbox(sbox_input^input_relation_delta), sbox(sbox_input));
            }
        }
    }
    pretty_print(differential_bias_table, argc,argv);
}
