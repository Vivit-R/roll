%{
    #include <stdio.h>
    #include <string.h>
    #include "roll.tab.h"
    #include "eval.h"
    #include "roll.h"
    #include "settings.h"
    #include "output.h"

    void yyerror(const char *msg);
    int yylex();

    void finish();
%}

%error-verbose

%start session

%union { int i; struct die *p; int b; char *s; }



/* Meta-commands */
%token EXIT
%token PRINT
%token SET

/* Linsolv-requested playing cards */
%token DRAW

/* Options */
%token VERBOSE
%token NOVERBOSE

/* An endline ends a statement */
%token ENDLINE

/* Parentheses, for association */
%token LPAREN
%token RPAREN

/* Token for unrecognized text */
%token WHAT

/* Primitive data */
%token STRING
%token NUMBER
%token PERCENT
%token TRUE
%token FALSE

/* Type declarations */
%type<i> NUMBER exp success_count eval conditional
%type<b> check
%type<p> roll

/* Conditional operators -- the query may be used binarily or ternarily; the
   colon is only used ternarily */
%right QUERY
%right COLON

/* Simple comparison operators -- these yield Booleans */
%right GE
%right LE
%right EQ
%right GT
%right LT

%right TILDE

/* Success-counting operators -- these yield integers */
%right EEQ
%right GGT
%right LLT
%right GGE
%right LLE
/* (Of course, it's C, so there isn't really a difference between an integer
   and a Boolean as far as the computer is concerned) */

/* Arithmetic operators */
%left PLUS MINUS
%left TIMES DIVIDE

%left BANG

/* The D */
%left DEE

%%
session:
    line session | exit {
        finish();
    }
;

line:
    DRAW ENDLINE {
        char *card = drawcard();
        printf("%s", card);
        free(card);
        printf("\n> ");
    } | eval {
        printf("\n> ");
    } | report_option ENDLINE {
        reportverbose();
        printf("> ");
    } | set ENDLINE {
        printf("> ");
    } | bad_input ENDLINE {
        printf("> ");
    } | ENDLINE {
        printf("> ");
    }
    ;

bad_input:
    error bad_input | error | WHAT bad_input | WHAT {
        printf("Sorry, I don't understand that.\n");
    }
    ;


set: SET VERBOSE {
         setverbose();
    } | SET NOVERBOSE {
         setnoverbose();
    }
    ;

report_option: VERBOSE | NOVERBOSE {
    }
    ;

exit:
    EXIT ENDLINE | {
        /* EOF behavior */
        printf("\n");
    }
    ;

roll:   DEE exp {
            $$ = d(1, $2);
    } | exp DEE {
            $$ = d($1, 6);
    } | DEE PERCENT {
            $$ = d(1, 100);
    } | exp DEE exp {
            $$ = d($1, $3);
    }
    ;

exp:
    NUMBER {
        $$ = $1;

    } | roll BANG {
        explode($1, 0);
        $$ = destructive_sumdice($1);
    } | roll {
        $$ = destructive_sumdice($1);
    } | conditional {
        $$ = $1;
    } | success_count {
        $$ = $1;
    } | LPAREN exp RPAREN {
        $$ = $2;
    } | exp PLUS exp {
        $$ = $1 + $3;
    } | exp TIMES exp {
        $$ = $1 * $3;
    } | exp MINUS exp {
        $$ = $1 - $3;
    } | exp DIVIDE exp {
        $$ = 0;
        if ($3 != 0) {
            $$ = $1 / $3;
        } else {
            yyerror("Division by zero!");
        }
    }
    ;

eval:
    NUMBER ENDLINE {
        $$ = $1;
        reportresult("Value: ", $$);
    } | check ENDLINE {
        $$ = $1;
        reportsuccess($$);
    } | exp ENDLINE {
        $$ = $1;
        reportresult("Result: ", $$);
    } | success_count ENDLINE {
        $$ = $1;
        reportresult("Success(es): ", $$);
    }
    ;

success_count:
    roll GGT exp {
        /* Ugly kludge with the frees here, FIXME pls */
        $$ = countsuccesses($1, $3, ">");
        freedice($1);
    } | roll LLT exp {
        $$ = countsuccesses($1, $3, "<");
        freedice($1);
    } | roll GGE exp {
        $$ = countsuccesses($1, $3, ">=");
        freedice($1);
    } | roll LLE exp {
        $$ = countsuccesses($1, $3, "<=");
        freedice($1);
    } | roll EEQ exp {
        $$ = countsuccesses($1, $3, "=");
        freedice($1);
    }
    ;

conditional:
    check QUERY exp {
        $$ = 0;
        if ($1) {
            $$ = $3; 
        }
    } | check QUERY exp COLON exp {
        $$ = $5;
        if ($1) {
            $$ = $3; 
        }
    }

check:
    TRUE {
        $$ = 1;
    } | FALSE {
        $$ = 0;
    } | exp EQ exp { 
        $$ = ($1 == $3);
    } | exp GT exp {
        $$ = ($1 > $3);
    } | exp LT exp {
        $$ = ($1 < $3);
    } | exp GE exp {
        $$ = ($1 >= $3);
    } | exp LE exp {
        $$ = ($1 <= $3);
    }


%%

void yyerror(const char* msg) {
    fprintf(stderr, "I AM ERROR: %s\n", msg);
    flushmsg();
}
