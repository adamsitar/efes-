#!/usr/bin/env bash
# Send keystrokes to the running DOSBox-X window (live session).
#
# Usage:  ./utils/keys.sh KEY [KEY ...]
#   KEY is xdotool syntax:  F2 F7 F8 F9 Return Escape Tab alt+x ctrl+F2
#   or:  --type 'TEXT'  to type literal text (the next argument, no Enter).
#
# Examples:
#   ./utils/keys.sh --type 'EDD' Return          # run EDD at the prompt
#   ./utils/keys.sh F9                           # TD: run program
#   ./utils/keys.sh alt+x                        # TD: quit
#
# Mechanism notes (hard-won, don't regress):
#   - Keys go via XTEST: it is the only channel DOSBox-X receives F-keys
#     through (XSendEvent --window works for plain chars but drops F1-F10).
#   - XTEST follows X input focus, and under WSLg the focus is yanked back
#     whenever the user touches another Windows window. So: focus, VERIFY,
#     send, re-verify; loud warning if focus was stolen mid-burst - then
#     the caller must screenshot.sh and re-send.
#   - usescancodes=false in dos-live.sh is required; raw scancode mode
#     garbles synthetic keys ('EDD' arrives as '1)=88...').
#   - keyup of stray modifiers first: a latched Shift turns F3 into
#     shift+F3, which TD ignores.

set -u

if [[ $# -eq 0 ]]; then
    echo "Usage: $0 [--type 'TEXT'] KEY ..."
    exit 1
fi

WID="$(xdotool search --name 'DOSBox-X' 2>/dev/null | head -1)"
if [[ -z "$WID" ]]; then
    echo "No DOSBox-X window found. Start one with ./utils/dos-live.sh"
    exit 1
fi

xdotool windowraise "$WID" 2>/dev/null

# Acquire focus and verify we truly have it (WSLg steals it back at will).
GOT=
for _ in $(seq 1 10); do
    xdotool windowfocus --sync "$WID" 2>/dev/null
    sleep 0.15
    if [[ "$(xdotool getwindowfocus 2>/dev/null)" == "$WID" ]]; then GOT=1; break; fi
done
if [[ -z "$GOT" ]]; then
    echo "WARNING: could not focus DOSBox-X window; keys NOT sent."
    exit 1
fi

xdotool keyup shift ctrl alt super 2>/dev/null
sleep 0.1

while [[ $# -gt 0 ]]; do
    if [[ "$1" == "--type" ]]; then
        shift
        xdotool type --delay 100 -- "$1"
    else
        xdotool key --clearmodifiers -- "$1"
    fi
    sleep 0.25
    shift
done

if [[ "$(xdotool getwindowfocus 2>/dev/null)" != "$WID" ]]; then
    echo "WARNING: focus was stolen while sending; some keys may be lost."
    echo "Verify with ./utils/screenshot.sh before continuing."
    exit 2
fi
