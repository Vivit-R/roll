%{
    #include <stdlib.h>
    #include <stdio.h>
    #include "roll.tab.h"

%}

%option noyywrap

%%
set         { return SET ;}
verbose     { return VERBOSE; }
noverbose   { return NOVERBOSE; }
exit        { return EXIT; }

d           { return DEE; }

(kl|dh)     { return DROPHIGH; }
(kh|dl)     { return DROPLOW; }

[0-9]+      { yylval.i = atoi(yytext); return NUMBER; }
%           { return PERCENT; }

\+          { return PLUS; }
\-          { return MINUS; }
\*          { return TIMES; }
\/          { return DIVIDE; }

\(          { return LPAREN; }
\)          { return RPAREN; }

\>=         { return GE; }
\<=         { return LE; }
\=          { return EQ; }
\<          { return LT; }
\>          { return GR; }
\>>         { return GGR; }
\<<         { return LLT; }
\>>=        { return GGE; }
\<<=        { return LLE; }

\n          { return ENDLINE; }
[ \t]       ;
[^+-/*]     { return WHAT; }
%%
