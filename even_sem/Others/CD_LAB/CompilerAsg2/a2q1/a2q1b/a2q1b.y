/*
Change your grammar to recognise strings with equal numbers of "a"s and "b"s - now which is best? 
The best Lex can do is as done in previous part, and then count the 'a's and 'b's in the action
to make sure they match. 

Yacc e.g.: 
  a_b	: 'a' a_b 'b' | 'a' 'b' ;

I would use the Yacc version. 
*/

%{
#include<stdio.h>
#include<stdlib.h>
int yyerror (char *s);
int yylex();
%}

%token a b

%%
s : a s b | a b ;
%%


int yywrap() {
	return 1;
}

int yyerror(char *s) {
	printf("Expression is Rejected! It is NOT of form a^nb^n.\n");
	exit(0);
}

int main() {
	printf("\nEnter an expression : ");
	yyparse();	 // reads a token value pair from yylex()
	printf("Expression is Accepted! It is of form a^nb^n.\n");
	return 0;
}
