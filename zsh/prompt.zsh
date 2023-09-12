#!/bin/zsh    

# Colors:
#   0   Black
#   1   Red
#   2   Green
#   3   Yellow
#   4   Blue
#   5   Magenta
#   6   Cyan
#   7   White
#   8   Bright Black
#   9   Bright Red
#  10   Bright Green
#  11   Bright Yellow
#  12   Bright Blue
#  13   Bright Magenta
#  14   Bright Cyan
#  15   Bright White


# Color definitions
autoload -U colors && colors
USER_COLOR="%F{1}"
AT_COLOR="%F{8}"
HOSTNAME_COLOR="%F{2}"
DIRECTORY_COLOR="%F{4}"
GIT_COLOR="%F{14}"

# Git stuff
autoload -Uz vcs_info
precmd_vcs_info() { vcs_info }
precmd_functions+=( precmd_vcs_info )
setopt prompt_subst
zstyle ':vcs_info:git:*' formats "[ ${GIT_COLOR} %b%f ]"

# Prompt
PROMPT="[%F{10}+${reset_color}] ${USER_COLOR}%n${reset_color}${AT_COLOR}@%f${HOSTNAME_COLOR}%m${reset_color}: ${DIRECTORY_COLOR} %(5~|%-1~/.../%3~|%4~)%f "
PROMPT+='${vcs_info_msg_0_}'
PROMPT+="
  󱞩 "
