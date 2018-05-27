/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_ROLL_TAB_H_INCLUDED
# define YY_YY_ROLL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    EXIT = 258,
    PRINT = 259,
    SET = 260,
    DRAW = 261,
    VERBOSE = 262,
    NOVERBOSE = 263,
    ENDLINE = 264,
    LPAREN = 265,
    RPAREN = 266,
    WHAT = 267,
    STRING = 268,
    NUMBER = 269,
    PERCENT = 270,
    TRUE = 271,
    FALSE = 272,
    QUERY = 273,
    COLON = 274,
    GE = 275,
    LE = 276,
    EQ = 277,
    GT = 278,
    LT = 279,
    TILDE = 280,
    EEQ = 281,
    GGT = 282,
    LLT = 283,
    GGE = 284,
    LLE = 285,
    PLUS = 286,
    MINUS = 287,
    TIMES = 288,
    DIVIDE = 289,
    BANG = 290,
    DEE = 291
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 "roll.y" /* yacc.c:1909  */
 int i; struct die *p; int b; char *s; 

#line 94 "roll.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_ROLL_TAB_H_INCLUDED  */
