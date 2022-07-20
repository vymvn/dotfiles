#!/bin/bash

# Set the source audio player here.
# Players supporting the MPRIS spec are supported.
# Examples: spotify, vlc, chrome, mpv and others.
# Use `playerctld` to always detect the latest player.
# See more here: https://github.com/altdesktop/playerctl/#selecting-players-to-control
PLAYER="spotify"

# Format of the information displayed
# Eg. {{ artist }} - {{ album }} - {{ title }}
# See more attributes here: https://github.com/altdesktop/playerctl/#printing-properties-and-metadata

PLAYERCTL_STATUS=$(playerctl --player=$PLAYER status 2>/dev/null)
FORMAT="["$PLAYERCTL_STATUS"] {{ artist }} - {{ title }}"
EXIT_CODE=$?

if [ $EXIT_CODE -eq 0 ]; then
    STATUS=$PLAYERCTL_STATUS
else
    # STATUS="No player is running"
	:
fi

if [ "$1" = "--status" ]; then
    echo "$STATUS"
else
    if [ "$STATUS" = "Stopped" ]; then
        # echo "No music is playing"
		:
    elif [ "$STATUS" = "Paused"  ]; then
	polybar-msg action "#spotify-play-pause.hook.1" 1>/dev/null 2>&1
        playerctl --player=$PLAYER metadata --format "$FORMAT"
    elif [ "$STATUS" = "Playing" ]; then
	    polybar-msg action "#spotify-play-pause.hook.0" 1>/dev/null 2>&1
        playerctl --player=$PLAYER metadata --format "$FORMAT"
    else
		:
    fi
fi

