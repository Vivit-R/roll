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
%}

%error-verbose

%start rolls

%union { int i; }

%token DEE
%token DROPHIGH
%token DROPLOW
%token PERCENT
%token EXIT

%token SET
%token VERBOSE
%token NOVERBOSE

%token GE
%token LE
%token EQ
%token GR
%token LT
%token GGR
%token LLT
%token GGE
%token LLE

%token ENDLINE

%token LPAREN
%token RPAREN

%token WHAT

%token NUMBER
%type<i> NUMBER exp roll

%left PLUS
%left MINUS
%left TIMES
%left DIVIDE

%%
rolls: line rolls | exit
;

line:
    exp ENDLINE {
        queuemsg("Result: ");
        queuenum($1);
        printmsg();
        printf("\n> ");
    } | report_option ENDLINE {
        reportverbose();
        printf("> ");
    } | set ENDLINE {
        printf("> ");
    } | bad_input ENDLINE {
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

exit: EXIT ENDLINE
    {
        return 0;
    }
    ;

roll:   DEE NUMBER {
            $$ = d(1, $2);
    } | NUMBER DEE {
            $$ = d($1, 6);
    } | DEE PERCENT {
            $$ = d(1, 100);
    } | NUMBER DEE NUMBER {
            $$ = d($1, $3);
    }
    ;

exp:
    roll | NUMBER {
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
        $$ = $1 / $3;
    }
    ;

operations:  DROPHIGH | DROPLOW | exp
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

void yyerror(const char* msg) {
    fprintf(stderr, "I AM ERROR: %s\n", msg);
}
