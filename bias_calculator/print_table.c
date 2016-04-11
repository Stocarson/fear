#include <stdio.h>
#include <stdlib.h>
#include "sbox0_definition.h"
#include "print_table.h"
extern FILE* yyin,*yyout;
static void wrong_args(char* exename) {
    printf("Usage: %s --csv <output file name>\n Or: %s --latex <output file name>\n",exename);
    exit(1);
}

void validate_args(int argc,char** argv) {
    if(argc!=3) {
        wrong_args(argv[0]);
    }
    if(strcmp(argv[1],"--csv") && strcmp(argv[1],"--latex")) {
        wrong_args(argv[0]);
    }
}
static void pretty_print_latex(int table[SBOX_INPUT_SIZE][SBOX_OUTPUT_SIZE],FILE* fptr) {
    int i,j;

    /* print the header */
    fprintf(fptr,"\\hline\n  ");
    for (i=0; i<SBOX_OUTPUT_SIZE; i++) {
        fprintf(fptr,"& %04X ",i);
    }
    fprintf(fptr,"\\\\\n\\hline");

    /* print the bias table, ## markers employed to ease Flex beautifier */
    for (i=0; i<SBOX_INPUT_SIZE; i++) {
        fprintf(fptr,"%04X ",i);
        for(j=0; j<SBOX_OUTPUT_SIZE; j++) {
            fprintf(fptr,"& ##%d## ",table[i][j]);
        }
        fprintf(fptr,"\\\\\n\\hline");
    }
}
static void pretty_print_csv(int table[SBOX_INPUT_SIZE][SBOX_OUTPUT_SIZE],FILE* fptr) {
    int i,j;

    /* print the header */
    /* First field empty is voluntarily empty */
    for (i=0; i<SBOX_OUTPUT_SIZE; i++) {
        fprintf(fptr,",%04X",i);
    }
    fprintf(fptr,"\n");
    /* print the bias table, ## markers employed to ease Flex beautifier */
    for (i=0; i<SBOX_INPUT_SIZE; i++) {
        fprintf(fptr,"%04X",i);
        for(j=0; j<SBOX_OUTPUT_SIZE; j++) {
            fprintf(fptr,",%d",table[i][j]);
        }
        fprintf(fptr,"\n");
    }

}
void pretty_print(int table[SBOX_INPUT_SIZE][SBOX_OUTPUT_SIZE],int argc,char** argv) {
    char tempfile[]="/tmp/biastmpXXXXXX";
    if(!strcmp(argv[1],"--latex")) {
        int fd = mkstemp(tempfile);
        unlink(tempfile);
        FILE* tmpf=fdopen(fd,"w+");
        pretty_print_latex(table,tmpf);
        rewind(tmpf);
        yyin=tmpf;
        yyout = fopen(argv[2],"w+");
        yylex();
        fclose(yyout);
        fclose(tmpf);
        yyin=NULL;
        yyout=NULL;
    }
    if(!strcmp(argv[1],"--csv")) {
        FILE* out=fopen(argv[2],"w+");
        pretty_print_csv(table,out);
        fclose(out);

    }
}

