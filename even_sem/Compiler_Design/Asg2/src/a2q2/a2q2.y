%{
#include<stdio.h>
#include<stdlib.h>
int yylex(void);
int yyerror(char *);
%}

/* BISON Declarations */
%token  id
%left '+' '-'	/* Arithmatic Operators */
%left '*' '/'	/* Arithmatic Operators */
%left '(' ')'	/* Braces */
%left '|' '&'	/* Boolean Operators */
%left '!'		/* Negation */
%left neg		/* Unary minus */


/* Grammar Follows */
%%
E1  : E { printf("Value of the above expression is = %d\n", $1);}

E   : E '+' E { $$ = $1 + $3;}
	| E '-' E { $$ = $1 - $3;}
	| E '*' E { $$ = $1 * $3;}
	| E '/' E { $$ = $1 / $3;}
	| E '|' E { $$ = $1 | $3;}
	| E '&' E { $$ = $1 & $3;}
	| '!' E   { $$ = !$2;}
	| '-' E %prec neg{ $$ = -1 * $2;}
	| '(' E ')' { $$ = $2;}
	| id { $$ = $1;}
	;
%%


int main(){
	printf("\nEnter an expression : ");
	yyparse();	
	return 0;
}

int yywrap(){
	return 0;
}

int yyerror( char* s){
	printf("Invalid expression! Try Again.\n");
	exit(0);
	return 0;
}
