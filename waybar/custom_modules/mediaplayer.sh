#!/bin/bash


# Use playerctl's --follow to listen for changes in both status and metadata in real time
playerctl --player=$PLAYER_NAME metadata --format '{{artist}} - {{title}}' --follow &
playerctl --player=$PLAYER_NAME status --follow | while read -r status; do


    # Dynamically get the first available player name
    PLAYER_NAME=$(playerctl -l | head -n 1)

    # If no player is available, exit the script
    if [[ -z "$PLAYER_NAME" ]]; then
        echo "No media player found."
        exit 1
    fi
    # Get the current track info
    track_info=$(playerctl --player=$PLAYER_NAME metadata --format '{{artist}} - {{title}}' 2>/dev/null)

    # Check if it's an ad (for Spotify)
    TRACK_ID=$(playerctl --player=$PLAYER_NAME metadata mpris:trackid 2>/dev/null)

    if [[ $TRACK_ID == *":ad:"* ]]; then
        OUTPUT="AD PLAYING"
    elif [[ -n "$track_info" ]]; then
        OUTPUT="$track_info"
    else
        OUTPUT=""
    fi

    # Update the output based on the status
    if [[ "$status" != "Playing" && -n "$OUTPUT" ]]; then
        OUTPUT="󰏤 $OUTPUT"
    fi

    # Format the output directly
    JSON_OUTPUT=$(printf '{"text": "%s", "class": "custom-%s", "alt": "%s"}\n' "$OUTPUT" "$PLAYER_NAME" "$PLAYER_NAME")

    # Output to stdout for Waybar to pick up
    echo "$JSON_OUTPUT"

done
