#!/bin/bash

#
# This script opens all the reference URLs
#

THIS_DIR=$(dirname "$0")
source "$THIS_DIR/utils.sh"

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

trap _term SIGTERM SIGINT

UNIQUE_REFERENCES=$(GetAllReferenceURLs | sort --unique)
NUMBER_LINES=$(echo "$UNIQUE_REFERENCES" | wc -l)

echo "Number of URLs: " $NUMBER_LINES
echo "Estimated time to finish: " $(($NUMBER_LINES * $SLEEP_SECONDS * 2)) " seconds"

while IFS= read -r url; do
    no_space_url="${url// /}"
    if [ ! -z "$no_space_url" ]; then
        OpenUrlAndSleep "$no_space_url"
        OpenUrlAndSleep "$no_space_url?ref=rp"
    fi
done <<< "$UNIQUE_REFERENCES"
