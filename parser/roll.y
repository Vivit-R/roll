%{
    #include <stdio.h>
    #include <string.h>
    #include "roll.tab.h"
    #include "eval.h"
    #include "roll.h"
    #include "settings.h"
    
    void yyerror(const char *msg);
    int yylex();
%}

%error-verbose

%start rolls

%union { int i; }

%token DEE
%token DROPHIGH
%token DROPLOW
%token EX
%token PERCENT
%token PLUS
%token MINUS
%token MULT
%token DIV

%token VERBOSE
%token NOVERBOSE

%token GREQUAL
%token LEQUAL
%token EQUAL
%token GREATERTHAN
%token LESSTHAN
%token ENDLINE

%token NUMBER
%type<i> NUMBER

%%
rolls: roll endline | roll endline rolls | option endline rolls
;

option: verbose | noverbose
;

verbose: VERBOSE {
             verbose = 1;
         }

noverbose: NOVERBOSE {
             verbose = 0;
         }

endline: ENDLINE
        {
            printf("> ");
        }
        ;

roll:   DEE NUMBER {
            d(1, $2);
    } | NUMBER DEE {
            d($1, 6);
    } | DEE PERCENT {
            d(1, 100);
    } | NUMBER DEE NUMBER {
            d($1, $3);
    } | explode {}
    ;

explode:    EX NUMBER {
                x(1, $2);
    } | NUMBER EX {
                x($1, 6);
    } | EX PERCENT {    /* Dunno why you'd want this, but just in case */
                x(1, 100);
    } | NUMBER EX NUMBER {
                x($1, $3);
    }
    ;

arithmetic:  PLUS | MINUS | MULT | DIV
    {
        printf("NOBODY SAID THERE'D BE MATH!!\n");
    }
    ;

operations:  DROPHIGH | DROPLOW | arithmetic
    {
        printf("I SAID, NOBODY SAID THERE WOULD BE MATH!\n");
    }
    ;

evaluable:  operations NUMBER | evaluable 
    {
        printf("MAAAAATH");
    }
    ;

%%
/*
int main() {
    yyparse();
    return 0;
}
*/
void yyerror(const char* msg) {
    fprintf(stderr, "I AM ERROR: %s\n", msg);
}
