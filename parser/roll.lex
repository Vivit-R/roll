%{
    #include <stdlib.h>
    #include <stdio.h>
    #include "roll.tab.h"

%}

%option noyywrap

%%

 /* Comments, to be ignored by the compiler */
#.*         ;

 /* REPL meta-commands, not part of the language proper */
set         { return SET ;}
exit        { return EXIT; }
quit        { return EXIT; }
print       { return PRINT; }

 /* Linsolv-requested playing cards */
draw        { return DRAW; }

 /* Options */
verbose     { return VERBOSE; }
noverbose   { return NOVERBOSE; }

 /* Dice operator. Highest precedence. */
[dD]        { return DEE; }

 /*
(kl|dh)     { return DROPHIGH; }
(kh|dl)     { return DROPLOW; }
 */

 /* Primitive data. The percent sign is included for the purposes of "d%"-style
    notation.*/
\".*\"      { yylval.s = yytext; return STRING; }
[0-9]+      { yylval.i = atoi(yytext); return NUMBER; }
%           { return PERCENT; }
true        { return TRUE; }
false       { return FALSE; }

 /* Conditional characters. Ternary conditional is allowed, but the query
    is also allowed by itself -- the default alternative will be zero. */
\?          { return QUERY; }
\:          { return COLON; }

 /* Arithmetic operators */
\+          { return PLUS; }
\-          { return MINUS; }
\*          { return TIMES; }
\/          { return DIVIDE; }

 /* Parentheses, for associative purposes */
\(          { return LPAREN; }
\)          { return RPAREN; }

 /* Regular comparison operators, for checks */
\>=         { return GE; }
\<=         { return LE; }
\=          { return EQ; }
\<          { return LT; }
\>          { return GT; }

 /* Counting comparison operators (for dice pool mechanics) */
\==         { return EEQ; }
\>>         { return GGT; }
\<<         { return LLT; }
\>>=        { return GGE; }
\<<=        { return LLE; }

 /* Endlines end statements */
\n          { return ENDLINE; }

 /* Ignore whitespace */
[ \t]       ;

 /* Any other string of characters is considered erroneous */
[^+-/*]     { return WHAT; }
%%
