%{
#include<stdio.h>
%}

%%
\n 				{ return 1; }
[a]+[b]+\n  	{  return 0; }
exit  			{ exit(0); }
. 				;
%%

int yywrap() {
	return 0;
}

int main(){
	int tmp;
	while(1) {
		printf("\nEnter an expression : ");
		tmp = yylex();
		if(!tmp) printf("Expression is Accepted! It is of form a^nb^m.\n");
		else printf("Expression is Rejected! It is NOT of form a^nb^m.\n");
	}	
	return 0;
}
