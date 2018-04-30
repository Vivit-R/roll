%{
    #include <stdlib.h>
    #include "roll.tab.h"

%}

%option noyywrap

%%
verbose     { return VERBOSE; }
noverbose   { return NOVERBOSE; }
d           { return DEE; }
(kl|dh)     { return DROPHIGH; }
(kh|dl)     { return DROPLOW; }
x           { return EX; }
[0-9]+      { yylval.i = atoi(yytext); return NUMBER; }
%           { return PERCENT; }
\+          { return PLUS; }
-           { return MINUS; }
\*          { return MULT; }
\/          { return DIV; }
\>=         { return GREQUAL; }
\<=         { return LEQUAL; }
\=          { return EQUAL; }
\<          { return LESSTHAN; }
\>          { return GREATERTHAN; }
\n          { return ENDLINE; }
[ \t]       ;
%%
