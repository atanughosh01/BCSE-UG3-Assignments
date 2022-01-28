/* Write a lex file to count the number of words in an input text that start with a vowel */

%{
    int cnt_vowels = 0;
%}

%%

[aeiouAEIOU][a-zA-z0-9]* {
    cnt_vowels++;
}

[a-zA-Z0-9]* ;

. ;

%%

int yywrap(void){
    return 1;
}

int main() {
    printf("Enter one/more lines of numbers below :-\n");

    yylex();

    printf("\n-----------------------------------------------------\n");
    printf(" Total number of words starting with a vowel : %d\n", cnt_vowels);
    printf("-----------------------------------------------------\n");

    return 0;
}
