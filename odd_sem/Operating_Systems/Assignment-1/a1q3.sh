#!/usr/bin/bash

#Write a shell script to count the number of lines in a file.
 
echo -n "Enter the filepath: "
read filepath
number_of_lines=`wc --lines < $filepath`
echo "Number of lines in $filepath is = $number_of_lines"
