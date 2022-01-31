/* Write a lex program to identify the tokens of a for loop of C code and
 print the tokens along with the lexemes and their positions in the code. */

%{
/* Header */
#include<stdio.h>

/* Initialize counters */
int col = 1, row = 0;
%}

/* Logic for scanning through the for loop and do the needful */
%%
[" "\t] 							{col += 1;}	
[\n] 								{row += 1; col = 0;}
else|if|for|int|float|void|return	{row += 1; printf("%d\t%d\t%s\t<keyword>\n", row, col, yytext);}
[A-Za-z][A-Za-z0-9]*				{col += 1; printf("%d\t%d\t%s\t<identifier>\n", row, col, yytext);}
= 									{col += 1; printf("%d\t%d\t%s\t<assignment operator>\n", row, col, yytext);}
[<>]								{col += 1; printf("%d\t%d\t%s\t<relational operator>\n", row, col, yytext);}
"++"								{col += 1; printf("%d\t%d\t%s\t<increment operator>\n", row, col, yytext);}
"--"								{col += 1; printf("%d\t%d\t%s\t<decrement operator>\n", row, col, yytext);}
"=="								{col += 1; printf("%d\t%d\t%s\t<equal to operator>\n", row, col, yytext);}
"+"|"-"|"*"|"/" 					{col += 1; printf("%d\t%d\t%s\t<arithmetic operator>\n", row, col, yytext);}
[;,(){}]							{col += 1; printf("%d\t%d\t%s\t<delimeter>\n", row, col, yytext);}
[0-9]+\.[0-9]+						{col += 1; printf("%d\t%d\t%s\t<floating point variable>\n", row, col, yytext);}
[0-9]+ 								{col += 1; printf("%d\t%d\t%s\t<integer variable>\n", row, col, yytext); }
.									{printf("%s\tINVALID\n",yytext); }
%%


/* This routine is called whenever the scanner reaches the end of file. If yywrap() returns 1,
the scanner continues with normal wrapup on the end of input. */
int yywrap() { 
	return 1;
}

/* Main Function */
int main() {
	
	printf("\nROW\tCOL\tLEXEME\tTYPE\n\n");
	yyin = fopen("input.txt", "r");

	/* Implies the main entry point for lex, reads the input stream generates tokens,
	returns zero at the end of input stream . It is called to invoke the lexer
	(or scanner) and each time yylex() is called, the scanner continues processing
	the input from where it last left off. */

	yylex();
	return 0;
}
