 #!/usr/bin/bash

bison -d a2q1b.y
flex a2q1b.l
gcc lex.yy.c a2q1b.tab.c -o ./res1b.exe
./res1b.exe
rm -rf lex.yy.c a2q1b.tab.c a2q1b.tab.h res1b.exe
