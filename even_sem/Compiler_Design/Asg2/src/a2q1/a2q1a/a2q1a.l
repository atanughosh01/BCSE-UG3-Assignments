%{
#include "a2q1a.tab.h"
%}

%%
a   { return a; }
b   { return b; }
\n  { return 0; }
.   { return yytext[0]; }
%%
