#!/usr/bin/bash

#Write a shell script that counts the number of ordinary files (not directories) in the current
#working directory and its sub-directories.

number_of_files=`find . -type f -print | wc -l`
echo "Number of files in current direactory and sub-directories are = $number_of_files"
