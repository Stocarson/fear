.PHONY: clean

all: linbiasgen diffbiasgen 

print_table.o: print_table.c sbox_definition.h print_table.h 
	gcc -c print_table.c

linbiasgen: linbiasgen.c sbox_definition.h print_table.o latex_lex.o
	gcc -ggdb linbiasgen.c print_table.o latex_lex.o -o linbiasgen

diffbiasgen: diffbiasgen.c sbox_definition.h print_table.o latex_lex.o
	gcc diffbiasgen.c print_table.o latex_lex.o -o diffbiasgen

latex_lex.o: prettyprint.l
	flex prettyprint.l
	gcc -c -o latex_lex.o lex.yy.c

clean:
	rm -f lex.yy.c linbiasgen diffbiasgen *.o
