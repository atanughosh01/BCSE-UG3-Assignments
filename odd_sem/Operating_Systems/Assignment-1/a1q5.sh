#!/usr/bin/bash

# Write a shell program to duplicate the UNIX rm command with the following features:
# a. Instead of deleting the files, it will move them to a my-deleted-files directory. If the file
# already exists in the my-deleted-files directory, then the existing file (in the my-deletedfiles) 
# will have the version number zero appended to it and the newly deleted file will have
# version number one appended to it.
# b. The command will have a switch -c that will clear the entire my-deleted-files directory
# after asking for confirmation. 


trashBin="$HOME/my-deleted-files"
if [ -e "$trashBin" ] ; then #Trash location exists
    if ! [ -d $trashBin ] ; then #Trash is not a directory
        echo "$trashBin exists and is already a file!"
        exit 1
    fi
else #Trash location does not exist
    mkdir "$trashBin"
fi

usage() {
    local progname
    progname=$1
    echo "Usage: $progname <filename1> <filename2> ..."
    echo -e "\tSafely removes files"
    echo "Usage: $progname -c"
    echo -e "\tClears $trashBin directory"
}

while getopts ":c" opt; do
    case $opt in
        "c")
            #Clear trashBin
            echo -n "Are you sure you want to clear ${trashBin}?[Y/N] "
            read answer
            answer=${answer##+( )} #Remove leading whitespace
            answer=${answer:0:1} #Get first char
            if [ $answer = 'Y' -o $answer = 'y' ] ; then
                for file in "$trashBin"/* ; do
                    if ! [ -e "$file" ] ; do
                        continue
                    fi
                    rm -rf "$file"
                done
            fi
            exit #No other option considered
            ;;
        *)
            usage "$0"
            exit 1
            ;;
    esac
done
shift $(($OPTIND - 1))

if [ $# -lt 2 ] ; then #Missing filenames
    usage "$0"
    exit 1
fi

for file in $* ; do
    if ! [ -e "$file" ] ; then 
        echo "Cannot delete; $file does not exist; sorry"
        continue
    elif [ -d "$file" ] ; then
        echo "Cannot delete; $file is a directory; sorry"
        continue
    fi
    fileName=${file##*/} #Extract just the file name at the end
    if ! [ -e "$trashBin/$fileName" -o -e "$trashBin/$fileName.0" -o -e "$trashBin/$fileName.1" ] ; then #we need no version number
        mv "$file" "$trashBin/$fileName"
        continue
    elif ! [ -e "$trashBin/$fileName.0" -o -e "$trashBin/$fileName.1" ] ; then #version numbers 0 and 1 would suffice
        mv "$trashBin/$fileName" "$trashBin/$fileName.0"
        mv "$file" "$trashBin/$fileName.1"
        continue
    fi
    versionNumber=2 #new version number supposedly
    while [ -e "$trashBin/$fileName.$versionNumber" ] ; do
        versionNumber=$((versionNumber+1))
    done
    mv "$file" "$trashBin/$fileName.$versionNumber"
done
