#!/bin/bash

#
# This script opens all the URLs in the given file
#


_term() {
    echo "Caught SIGTERM signal!"
    echo "Killing child processes: $(jobs -p)"
    kill -9 $(jobs -p)

    exit 0
}


if [ $# -ne 1 ]; then
    echo "Usage: $(basename $0) file"
fi

trap _term SIGTERM SIGINT

FILE="$1"
SLEEP_SECONDS=16
NUMBER_LINES=$(wc -l "$FILE" | awk '{ print $1 }')

echo "Processing URL file: " "$FILE"
echo "  number of lines: " $NUMBER_LINES
echo "  estimated time to finish: " $(($NUMBER_LINES * $SLEEP_SECONDS)) " seconds"

while IFS=" " read -r field1 url; do
    no_space_url="${url// }"
    if [ ! -z "$no_space_url" ]; then
        echo "Opening: $no_space_url"

        firefox --new-tab "$no_space_url" &

        sleep $SLEEP_SECONDS
    fi
done <"$FILE"