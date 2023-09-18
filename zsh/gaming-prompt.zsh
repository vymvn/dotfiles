#!/bin/zsh

# Edit this to change the icon thats left
# on executing a command, i.e. transient

TRANSIENT_PROMPT='%F{15}$%f '

function set-prompt() {
    emulate -L zsh
    local REPLY

    # Default:
    #
    #  user @ host:  ~ ─────────────────────── [4:20:39]
    # $

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

    # Edit this abomination to change parts of the prompt
    fill-line "%F{5}%n%f %F{8}@%f %F{7}%m%f%F{8}:%f %F{4}%f %F{12}%~%f " " %F{black}[%*%f"

    PROMPT=$REPLY$'%F{0}]%f\n%F{15}$%f '
    RPROMPT=""
}


# Im way to stupid to come up with this shit myself
# This is heavily based on an explanation by romkatv
#
# Full credit to him my brain cant math nor logic:
# https://github.com/romkatv/

function prompt-length() {
    emulate -L zsh

    local -i COLUMNS=${2:-COLUMNS}
    local -i x
    local -i m
    local -i y=${#1}

    if (( y )); then
        while (( ${${(%):-$1%$y(l.1.0)}[-1]} )); do
            x=y
            (( y *= 2 ))
        done

        while (( y > x + 1 )); do
            (( m = x + (y - x) / 2 ))
            (( ${${(%):-$1%$m(l.x.y)}[-1]} = m ))
        done
    fi

    typeset -g REPLY=$x
}

function fill-line() {
    emulate -L zsh

    prompt-length $1
    local -i left_len=REPLY
    prompt-length $2 9999
    local -i right_len=REPLY

    local -i pad_len=$((COLUMNS - left_len - right_len - ${ZLE_RPROMPT_INDENT:-1}))

    if (( pad_len < 1 )); then
        typeset -g REPLY=$1
    else
        local pad=%F{black}${(pl.$pad_len..─.)}%f
        typeset -g REPLY="${1}${pad}${2}"
    fi
}

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
    zle && PROMPT=$TRANSIENT_PROMPT RPROMPT= zle reset-prompt && zle -R
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
