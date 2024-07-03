#!/bin/zsh

# Color definitions
autoload -U colors && colors
USER_COLOR="%F{1}"
AT_COLOR="%F{8}"
HOSTNAME_COLOR="%F{7}"
DIRECTORY_COLOR="%F{4}"
GIT_COLOR="%F{14}"

# Git stuff
autoload -Uz vcs_info
precmd_vcs_info() { vcs_info }
precmd_functions+=( precmd_vcs_info )
setopt prompt_subst
zstyle ':vcs_info:git:*' formats "[ ${GIT_COLOR} %b%f ]"

# TRANSIENT_PROMPT="[%F{10}+${reset_color}] "

# Function to set transient prompt based on last command status
set_transient_prompt() {
    if [[ $? -eq 0 ]]; then
        TRANSIENT_PROMPT="[%F{10}+${reset_color}] "
    else
        TRANSIENT_PROMPT="[%F{1}-${reset_color}] "
    fi
}

function set-prompt() {
    emulate -L zsh
    local REPLY

    # Default:
    #
    # [+] user@host:   ~ 
    #   󱞩 

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

    PROMPT="[%F{6}*${reset_color}] ${USER_COLOR}%n${reset_color}${AT_COLOR}@%f${HOSTNAME_COLOR}%m${reset_color}: ${DIRECTORY_COLOR}  %(5~|%-1~/.../%3~|%4~)%f ${vcs_info_msg_0_}"
    PROMPT+=$REPLY$'%f\n  󱞩 '
    RPROMPT=""
}

# I really dont know what any of this does I just stole it
[[ -c /dev/null ]]  || return
zmodload zsh/system ||  return

zle -N send-break _transient_prompt_widget-send-break
function _transient_prompt_widget-send-break {
    _transient_prompt_widget-zle-line-finish
    zle .send-break
}

zle -N zle-line-finish _transient_prompt_widget-zle-line-finish

function _transient_prompt_widget-zle-line-finish {
    (( ! _transient_prompt_fd )) && {
        sysopen -r -o cloexec -u _transient_prompt_fd /dev/null
        zle -F $_transient_prompt_fd _transient_prompt_restore_prompt
    }
    zle && set_transient_prompt && PROMPT=$TRANSIENT_PROMPT RPROMPT= zle reset-prompt && zle -R
}

function _transient_prompt_restore_prompt {
    exec {1}>&-
    (( ${+1} )) && zle -F $1
    _transient_prompt_fd=0
    set-prompt
    zle reset-prompt
    zle -R
}

(( ${+precmd_functions} )) || typeset -ga precmd_functions
(( ${#precmd_functions} )) || {
        do_nothing() {true}
        precmd_functions=(do_nothing)
}

precmd_functions+=_transient_prompt_precmd
function _transient_prompt_precmd {
        TRAPINT() { zle && _transient_prompt_widget-zle-line-finish; return $(( 128 + $1 )) }
}

setopt no_prompt_{bang,subst} prompt_{cr,percent,sp}
autoload -Uz add-zsh-hook
add-zsh-hook precmd set-prompt
