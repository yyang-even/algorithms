#!/bin/bash

#
# This script checks for duplicates
#


FILE="docs/done_list.md"


echo "Checking for duplicate entries in" "$FILE"
sort "$FILE" | uniq -d


echo "Checking for duplicate references."
while IFS=" " read -r field1 url; do
    no_space_url="${url// }"
    if [ ! -z "$no_space_url" ]; then
        grep_output=$(git grep "$no_space_url")
        line_count=$(echo "$grep_output" | wc -l)

        if [ $line_count -ne 2 ]; then
            echo "$grep_output"
            echo ""
        fi
    fi
done <"$FILE"
