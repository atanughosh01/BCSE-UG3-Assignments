#!/usr/bin/bash

# Extend the shell script written in (8) to perform the following task: User is asked to enter two
# different patterns or words. The first pattern will have to be matched with the contents of the
# file and replaced by the second pattern if a match occurs. If the first pattern does not occur in
# the file, an appropriate error message will be displayed.

echo -n "Enter file name: "
read filename
if ! [ -e "$filename" ] ; then
    echo "$filename: not found"
    exit 1
fi
echo -n "Enter a pattern to search for: "
read pattern
if ! grep -qE "${pattern}" < "$filename" ; then
    echo "$pattern: not found"
    exit 1
fi
echo -n "Enter text to replace $pattern with: "
read word
sed --line-length=0 --binary -E "--expression=s/${pattern}/${word}/g" -i "$filename"
