%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"
%}

socket_start "SOCKET"
multiple "MULTIPLE"
iopinmode "IOPINMODE"
pindef "PINDEF"
pindefend "PINDEFEND"
socket_end "END"
name [a-zA-Z][a-zA-Z0-9]{0,31}
number [0-9]{1,3}

%%

{socket_start} {return T_SOCKET_START;}
{multiple} {return T_MULTIPLE;}
{iopinmode} {return T_IOPINMODE;}
{pindef} {return T_PINDEF;}
{pindefend} {return T_PINDEF_END;}
{socket_end} {return T_SOCKET_END;}

{name} { 
    yylval.strval.str = yytext;
    yylval.strval.len = yyleng;
    return T_NAME;
}

{number} {
    yylval.intval = atoi(yytext);
    return T_NUMBER;
}

[\"=,] {return yytext[0];}

[ \t\n] {}

%%

int yywrap(void) {return 1;}

#ifdef DEBUG_SCANNER

int main(int argc, char **argv) {
    while(yylex());
    return 0;
}

#endif