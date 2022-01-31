#!/usr/bin/bash

lex $1
cc lex.yy.c -ll
./a.out
rm lex.yy.c
rm a.out
