#!/bin/bash


#PARENT_BAR="mybar"
#PARENT_BAR_PID=$(pgrep -a "polybar" | grep "$PARENT_BAR" | cut -d " " -f1)

FORMAT="{{artist}} - {{title}}"
STATUS=$(playerctl --player="spotify" status 2>/dev/null)

#echo $STATUS

playerctl metadata -f "$FORMAT"
