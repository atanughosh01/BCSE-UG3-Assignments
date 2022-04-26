 #!/usr/bin/bash
 
bison -d a2q1a.y
flex a2q1a.l
gcc lex.yy.c a2q1a.tab.c -o res1a.exe
./res1a.exe
rm -rf lex.yy.c a2q1a.tab.c a2q1a.tab.h res1a.exe
