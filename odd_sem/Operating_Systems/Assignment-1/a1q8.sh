#!/usr/bin/bash

# Write a shell script that accepts a file name as an input and performs the following activities
# on the given file. The program asks for a string of characters (that is, any word) to be provided
# by the user. The file will be searched to find whether it contains the given word. If the file
# contains the given word, the program will display (a) the number of occurrences of the word.
# The program is also required to display (b) the line number in which the word has occurred.
# (Note: the word may occur more than once in a given line) If the file does not contain the
# word, an appropriate error message will be displayed.

echo -n "Enter file name: "; read filename
if ! [ -e "$filename" ] ; then
    echo "$filename: not found"
    exit 1
fi
echo -n "Enter a word: "; read word
word=${word##+( )} ; word=${word%%+( )} #Remove leading and trailing whitespace
if ! grep -qE "\b${word}\b" < "$filename" ; then
    echo "$word: not found"
    exit 1
fi
nonunique_lines=$( command grep -onE "\b${word}\b" < "$filename" | command cut -d: -f1 )
num_words=$( command wc --lines <<< "$nonunique_lines" )
the_lines=$( command uniq <<< "$nonunique_lines" )
echo -e "Number of occurrences: $num_words. Line numbers on which they were found:\n$the_lines"
