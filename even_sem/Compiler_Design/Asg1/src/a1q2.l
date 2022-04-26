/*
Write a lex file to count the number of numbers appearing in the input.
Count the number of integers (without a decimal) separately from the
number of floating point numbers (with a decimal, and at least one
digit on either side of the decimal)
*/

%{
    int cnt_integers = 0, cnt_decimals = 0;
%}

%%

[0-9]+\.[0-9]+[ \t\n] {
    cnt_decimals++;
}

[0-9]+[ \t\n]+ {
    cnt_integers++;
}

. ;

%%


int yywrap(void){
    return 1;
}

int main() {

    printf("Enter one/more lines of numbers below :-\n");

    yylex();

    printf("\n---------------------------------------------------\n\t");
    printf("Total number of Integers: %d\n\t", cnt_integers);
    printf("Total number of decimals: %d\n", cnt_decimals);
    printf("---------------------------------------------------\n");

    return 0;
}
