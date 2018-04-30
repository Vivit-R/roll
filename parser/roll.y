%{
    #include <stdio.h>
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
rolls: roll ENDLINE | roll ENDLINE rolls | option ENDLINE rolls {
    verbose = 1;
}
;

option: verbose | noverbose
;

verbose: VERBOSE {
             verbose = 1;
         }

noverbose: NOVERBOSE {
             verbose = 0;
         }

roll:   DEE NUMBER {
            printf("%d\n", d(1, $2));
    } | NUMBER DEE {
            printf("%d\n", d($1, 6));
    } | DEE PERCENT {
            printf("%d\n", d(1, 100));
    } | NUMBER DEE NUMBER {
            printf("%d\n", d($1, $3));
    }
    ;

explode:    NUMBER EX NUMBER | EX NUMBER
    {
        printf("YOUR HEAD ASPLODE\n");
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

int main() {
    yyparse();
    return 0;
}

void yyerror(const char* msg) {
    fprintf(stderr, "I AM ERROR: %s\n", msg);
}
