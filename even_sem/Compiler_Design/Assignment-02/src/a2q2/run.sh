 #!/usr/bin/bash
 
bison -d a2q2.y
flex a2q2.l
gcc lex.yy.c a2q2.tab.c -o ./res.exe
./res.exe
rm -rf lex.yy.c a2q2.tab.c a2q2.tab.h res.exe
