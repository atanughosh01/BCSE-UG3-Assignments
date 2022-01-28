/* Write a lex file to count the number of lines, words, and characters in the input */

%{
int cnt_lines=0, cnt_words=0, cnt_chars=0;
%}

%%
\n {
    cnt_lines++;
}

[^ \t\n]+ {
    cnt_words++;
    cnt_chars += yyleng;
}

. {
    cnt_chars++;
}
%%


int yywrap(void) {
    return 1;
}

int main() {

    printf("Enter one/more lines of text below :-\n");

    yylex();

    printf("\n---------------------------------------------------\n\t");
    printf("Total number of lines present : %d\n\t", cnt_lines);
    printf("Total number of words present : %d\n\t", cnt_words);
    printf("Total number of chars present : %d\n", cnt_chars);
    printf("---------------------------------------------------\n");

    return 0;
}
