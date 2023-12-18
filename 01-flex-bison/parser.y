%{
#include <stdio.h>
#include <stdlib.h>
#include "sp.h"
int yylex(void);
void yyerror(const char *msg);
%}

%union {
        int intval;
        struct {
                char *str;
                int len;
        } strval;
}

%token <intval> T_NUMBER
%token <strval> T_NAME

%token T_SOCKET_START
%token T_MULTIPLE T_IOPINMODE
%token T_PINDEF T_PINDEF_END
%token T_SOCKET_END

%start socket_program

%%

socket_program: start_block basic_block pindef_block T_SOCKET_END {
                printf("\n\nSPC compiler done!\n");
        }
        ;

start_block: T_SOCKET_START '=' T_NAME ',' T_NUMBER {
                add_start_block($3.str, $3.len, $5);
        }
        ;

basic_block: multiple_block iopinmode_block {}
        ;

multiple_block: T_MULTIPLE '=' T_NUMBER {
                add_multiple_block($3);
        }
        ;

iopinmode_block: T_IOPINMODE '=' T_NUMBER {
                add_iopinmode_block($3);
        }
        ;

pindef_block: T_PINDEF pindef_list T_PINDEF_END {
                add_pindef_block();
        }
        ;

pindef_list: pindef_list_item {
                reset_chanels();       
        }
        | pindef_list pindef_list_item {
                reset_chanels();
        }
        ;

pindef_list_item: T_NUMBER '=' pindef_chanel_list ',' '"' T_NAME '"' {
                insert_pindef_list($1, $6.str, $6.len);
        }
        ;

pindef_chanel_list: T_NUMBER {
                insert_chanel_list($1);
        }
        | pindef_chanel_list ',' T_NUMBER {
                insert_chanel_list($3);
        }
        ;
%%

void yyerror(const char *msg) {
        printf("%s\n", msg);
}

int main(int argc, char **argv) {
        init_socket_program();
        yyparse();
        print_socket_program();
        return 0;
}