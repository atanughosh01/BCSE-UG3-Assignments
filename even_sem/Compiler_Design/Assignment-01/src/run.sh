#!/usr/bin/bash

lex $1
gcc lex.yy.c
./a.out
rm lex.yy.c
rm a.out
