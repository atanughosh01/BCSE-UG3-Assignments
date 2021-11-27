#!/usr/bin/bash

# Write a script called birthday_match.sh that takes two birthdays of the form DD/MM/YYYY
# (e.g., 15/05/2000) and returns whether there is a match if the two people were born on the
# same day of the week (e.g., Friday).

getWeekday() {
    local somedate
    local day
    local month
    local year
    somedate=$1 #Input date as first argument
    day=${somedate%%/*} ; year=${somedate##*/}
    month=${somedate#*/} ; month=${month%/*}
    date --date="$month/$day/$year" '+%A' 
}

echo -n "Enter first date: " ; read date1
echo -n "Enter second date: " ; read date2
weekday1=$(getWeekday $date1)
weekday2=$(getWeekday $date2)
echo "$date1 is on a $weekday1"
echo "$date2 is on a $weekday2"
if [ $weekday1 = $weekday2 ] ; then
    echo "Both dates fall on the same day of week."
else
    echo "Both dates do not fall on the same day of week."
fi
