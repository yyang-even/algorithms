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

SLEEP_SECONDS=16

OpenUrlAndSleep() {
    local URL="$1"
    echo "Opening: $URL"

    firefox --new-tab "$URL" &

    sleep $SLEEP_SECONDS
}


if [ $# -ne 1 ]; then
    echo "Usage: $(basename $0) <file>"
    exit 1
fi

trap _term SIGTERM SIGINT

FILE="$1"
NUMBER_LINES=$(wc -l "$FILE" | awk '{ print $1 }')

echo "Processing URL file: " "$FILE"
echo "  number of lines: " $NUMBER_LINES
echo "  estimated time to finish: " $(($NUMBER_LINES * $SLEEP_SECONDS * 2)) " seconds"

while IFS=" " read -r field1 url; do
    local no_space_url="${url// }"
    if [ ! -z "$no_space_url" ]; then
        OpenUrlAndSleep "$no_space_url"
        OpenUrlAndSleep "$no_space_url?ref=rp"
    fi
done <"$FILE"
