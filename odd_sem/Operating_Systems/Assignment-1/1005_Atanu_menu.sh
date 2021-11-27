#!/usr/bin/bash

# 1)
# Write a shell script with the name <last four digits of your roll
# no.>_firstname_menu.sh that repeatedly displays the following menu:
# [1] Find user [2] List large files [3] Disk usage [4] View Log File [5] Exit
# Your choice >
# If you enter any number other than [1 – 5], the script gives you an error message.
# If you enter 1 (Find user), the script will:
# • Prompt for a user name.
# • Displays result [whether it is a valid user or not].
# If you enter 2 (List large files), the script will:
# • Prompt for a size in bytes
# • List the names and sizes of all files greater than or equal to the specified size. If
# there are no files of that size, a blank list with headings only will be printed.
# If you enter 3 (Disk usage), result will be displayed appropriately.
# When you choose command 4 (View Log File), the script will display a file
# named logfile.txt with appropriate headings.
# Your script will create this file as follows: Every time a command is entered, you will
# append a line to a file named logfile.txt. The line will have the user name, the menu
# choice, and the output of the date command, separated by percent signs. The menu choice
# must be given in words, as shown in the sample output. Don’t just give the menu choice
# as a number—when you look at the log file a month from now, you want to know that a
# user did a “disk usage” command, not “3.”
# Invalid commands and the exit command do not have to be entered in the log file if you
# don’t want to.
# If you enter 5 (Exit), the script will exit.
# Menu options 1, 2, and 4 (find user, list large files, and view log file) must be
# implemented as separate functions. Add any other functions that you feel will make your
# job easier.

find_user() {
    local username
    echo -n "Enter username to search: "
    read username
    if command cut -d: -f1 < /etc/passwd | command grep -qF $username ; then 
        echo "$username is valid user."
    else
        echo "$username is not a valid user."
    fi
}

large_files() {
    local directory
    local size
    local file
    local filesize
    echo -n "Enter directory to search in (nothing for root directory): "
    read directory
    directory=${directory%%+(/)}
    echo -n "Enter size to filter for (in bytes): "
    read size
    echo -e "SIZE \t NAME"
    for file in "$directory"/* ; do
        if ! [ -e "$file" ] ; then
            continue
        fi 
        filesize=$(command stat --printf="%s" "$file")
        if [ $filesize -ge $size ] ; then
            echo -e "${filesize} \t ${file}"
        fi
    done
}

log_file() {
    echo -e "USER NAME \t OPTION NAME \t DATE"
    sed --line-length=0 --binary --expression="s/%/ \t /g" logfile.txt
}

PS3='Enter choice: '
select option_name in "Find user" "List large files" "Disk usage" "View log file" "Exit" ; do
    option=$REPLY
    echo "$(command whoami)%${option_name}%$(command date)" >> logfile.txt
    case $option in
        1)
            find_user
            ;;
        2)
            large_files
            ;;
        3)
            command df -h
            ;;
        4)
            log_file
            ;;
        5)
            exit
            ;;
        *)
            echo "Invalid option $option."
            ;;
    esac
done
