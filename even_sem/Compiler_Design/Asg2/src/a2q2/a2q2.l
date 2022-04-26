%{
 #include "a2q2.tab.h"
 extern int yylval;
%}

%%
[0-9]+      {yylval = atoi(yytext); return id;}
\n          {return 0;}             /* Return at newline */
[' '\t]+    {;}                     /* Skip Whitespace */
.           {return yytext[0];}     /* Return at . */
%%
