#!/bin/bash

# see man zscroll for documentation of the following parameters
zscroll -l 25 \
        --delay 0.1 \
        --scroll-padding " " \
        --match-command "`dirname $0`/get_spotify_status.sh --status 2>/dev/null" \
        --match-text "" "--scroll 0 --before-text ''" \
        --match-text "Playing" "--scroll 1 --before-text 'ﱘ '" \
        --match-text "Paused" "--scroll 0 --before-text 'ﱘ '" \
        --update-check true "`dirname $0`/get_spotify_status.sh" &

wait

