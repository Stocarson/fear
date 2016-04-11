%option noyywrap
%{
#include <stdio.h>
%}

%%

"##0##" { fprintf(yyout, "%c", yytext[2] ); } 
"##2##" { fprintf(yyout, "\\twobias{%c}", yytext[2] ); } 
"##-2##" { fprintf(yyout, "\\mtwobias{%c}", yytext[3] ); } 
"##4##" { fprintf(yyout, "\\fourbias{%c}", yytext[2] ); } 
"##-4##" { fprintf(yyout, "\\mfourbias{%c}", yytext[3] ); } 
"##6##" { fprintf(yyout, "\\sixbias{%c}", yytext[2] ); } 
"##-6##" { fprintf(yyout, "\\msixbias{%c}", yytext[3] ); } 
"##8##" { fprintf(yyout, "\\eightbias{%c}", yytext[2] ); } 
"##-8##" { fprintf(yyout, "\\meightbias{%c}", yytext[3] ); } 
"##16##" { fprintf(yyout, "\\sixteenbias{%c%c}", yytext[2] ,yytext[3] ); } 
%%

