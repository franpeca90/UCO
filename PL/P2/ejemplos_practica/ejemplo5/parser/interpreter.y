/*! 
  \file interpreter.y
  \brief Grammar file
*/




%{
#include <iostream>
#include <string>

/*******************************************/
/* NEW in example 5: pow */
#include <math.h>
/*******************************************/

/* Error recovery functions */
#include "../error/error.hpp"

/* Macros for the screen */
#include "../includes/macros.hpp"

/*! 
	\brief  Lexical or scanner function
	\return int
	\note   C++ requires that yylex returns an int value
	\sa     yyparser
*/
int yylex();


extern int lineNumber; //!< External line counter

/***********************************************************/
/* NEW in example 2 */
extern std::string progname; //!<  Program name
/***********************************************************/
%}

/* In case of a syntactic error, more information is shown */
%error-verbose

/* Initial grammar symbol */
%start program

/*******************************************/
/* NEW in example 4 */
/* Data type YYSTYPE  */
%union
{
  double number;  
}

/* Data type of the non-terminal symbol "exp" */
%type <number> exp
/*******************************************/

/* Defined token */

/* Minimum precedence */

/*******************************************/
/* NEW in example 5 */
%token SEMICOLON
/*******************************************/

/*******************************************/
/* MODIFIED in example 4 */
%token <number> NUMBER
/*******************************************/

/* Left associativity */

/*******************************************/
/* MODIFIED in example 3 */
%left PLUS MINUS 

/* NEW in example 5: MODULO */
%left MULTIPLICATION DIVISION MODULO

%left LPAREN RPAREN

%nonassoc  UNARY

/* Maximum precedence  */
/* NEW in example 5 */
%right POWER
/*******************************************/

%%
//! \name Grammar rules

program : stmtlist {  }
;

		/* MODIFIED in example 5: SEMICOLON */ 
stmtlist:  /* empty: epsilon rule */

		| stmtlist SEMICOLON     /* empty line */

		/* MODIFIED in example 4: the result of the expression is displayed  */ 
        | stmtlist exp SEMICOLON
            { 
				std::cout << BIYELLOW; 
				std::cout << "Result: ";
				std::cout << RESET; 
				std::cout << $2 << std::endl << std::endl;
            }

        | stmtlist error SEMICOLON
			{
				// The function yyerror is called
				// If %error-verbose is used then an error message is displayed
			}
;
 
		/* MODIFIED in example 3: tokens PLUS, MINUS, ... */
		/* NEW in example 3: unary operators */
		/* NEW in example 4: evaluation of the expressions */ 
		/* NEW in example 5: MODULO, POWER */
 exp:	NUMBER 
		{ $$ = $1; }

	| 	exp PLUS exp 
		{ $$ = $1 + $3; }

	| 	exp MINUS exp
      	{ $$ = $1 - $3; }

	| 	exp MULTIPLICATION exp 
		{ $$ = $1 * $3; }

	| 	exp DIVISION exp
		{ $$ = $1 / $3; }

	| 	LPAREN exp RPAREN
       	{ $$ = $2; }

		/* NEW in example 3 */
  	| 	PLUS exp %prec UNARY
		{ $$ = +$2; }

		/* NEW in example 3 */
	| 	MINUS exp %prec UNARY
		{ $$ = -$2; }

		/* NEW in example 5 */
	|	exp MODULO exp 
		{ $$ = (int) $1 % (int) $3; }

		/* NEW in example 5 */
	|	exp POWER exp 
     	{ $$ = pow($1,$3); }
;


%%




