/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_INTERPRETER_TAB_H_INCLUDED
# define YY_YY_INTERPRETER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    PRINT = 259,                   /* PRINT  */
    READ = 260,                    /* READ  */
    IF = 261,                      /* IF  */
    ELSE = 262,                    /* ELSE  */
    WHILE = 263,                   /* WHILE  */
    THEN = 264,                    /* THEN  */
    ENDIF = 265,                   /* ENDIF  */
    DO = 266,                      /* DO  */
    ENDWHILE = 267,                /* ENDWHILE  */
    REPEAT = 268,                  /* REPEAT  */
    UNTIL = 269,                   /* UNTIL  */
    FOR = 270,                     /* FOR  */
    FROM = 271,                    /* FROM  */
    STEP = 272,                    /* STEP  */
    ENDFOR = 273,                  /* ENDFOR  */
    SWITCH = 274,                  /* SWITCH  */
    VALUE = 275,                   /* VALUE  */
    DEFAULT = 276,                 /* DEFAULT  */
    ENDSWITCH = 277,               /* ENDSWITCH  */
    PRINTSTRING = 278,             /* PRINTSTRING  */
    READSTRING = 279,              /* READSTRING  */
    LETFCURLYBRACKET = 280,        /* LETFCURLYBRACKET  */
    RIGHTCURLYBRACKET = 281,       /* RIGHTCURLYBRACKET  */
    ASSIGNMENT = 282,              /* ASSIGNMENT  */
    COMMA = 283,                   /* COMMA  */
    NUMBER = 284,                  /* NUMBER  */
    BOOL = 285,                    /* BOOL  */
    VARIABLE = 286,                /* VARIABLE  */
    UNDEFINED = 287,               /* UNDEFINED  */
    CONSTANT = 288,                /* CONSTANT  */
    BUILTIN = 289,                 /* BUILTIN  */
    OR = 290,                      /* OR  */
    AND = 291,                     /* AND  */
    GREATER_OR_EQUAL = 292,        /* GREATER_OR_EQUAL  */
    LESS_OR_EQUAL = 293,           /* LESS_OR_EQUAL  */
    GREATER_THAN = 294,            /* GREATER_THAN  */
    LESS_THAN = 295,               /* LESS_THAN  */
    EQUAL = 296,                   /* EQUAL  */
    NOT_EQUAL = 297,               /* NOT_EQUAL  */
    NOT = 298,                     /* NOT  */
    PLUS = 299,                    /* PLUS  */
    MINUS = 300,                   /* MINUS  */
    CONCATENATION = 301,           /* CONCATENATION  */
    MULTIPLICATION = 302,          /* MULTIPLICATION  */
    DIVISION = 303,                /* DIVISION  */
    MODULO = 304,                  /* MODULO  */
    ENTIRE_DIVISON = 305,          /* ENTIRE_DIVISON  */
    LPAREN = 306,                  /* LPAREN  */
    RPAREN = 307,                  /* RPAREN  */
    UNARY = 308,                   /* UNARY  */
    POWER = 309                    /* POWER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 138 "interpreter.y"

  char * identifier; 				 /* NEW in example 7 */
  double number;  
  bool logic;						 /* NEW in example 15 */
  lp::ExpNode *expNode;  			 /* NEW in example 16 */
  std::list<lp::ExpNode *>  *parameters;    // New in example 16; NOTE: #include<list> must be in interpreter.l, init.cpp, interpreter.cpp
  std::list<lp::Statement *> *stmts; /* NEW in example 16 */
  lp::Statement *st;				 /* NEW in example 16 */
  lp::AST *prog;					 /* NEW in example 16 */

#line 129 "interpreter.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_INTERPRETER_TAB_H_INCLUDED  */
