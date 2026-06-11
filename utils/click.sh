#!/usr/bin/env bash
# Click inside the DOSBox-X window at window-relative coordinates.
# Coordinates are the SAME pixels you see in a screenshot.sh image
# (surface mode renders 1:1), so: screenshot, measure, click.
#
# Usage:  ./utils/click.sh X Y [BUTTON]     (BUTTON: 1=left default, 3=right)
#
# Why this exists: under WSLg the keyboard needs X focus, which is often
# unavailable (see keys.sh), but pointer events deliver by position alone.
# TD is fully mouse-driven, so menus/dialogs can be operated with clicks
# plus plain-character keys. Requires autolock=false (set by dos-live.sh),
# otherwise the first click captures the mouse and coordinates go relative.

set -u

if [[ $# -lt 2 ]]; then
    echo "Usage: $0 X Y [BUTTON]   (window-relative pixels, see screenshot.sh)"
    exit 1
fi

RX="$1"; RY="$2"; BTN="${3:-1}"

WID="$(xdotool search --name 'DOSBox-X' 2>/dev/null | head -1)"
if [[ -z "$WID" ]]; then
    echo "No DOSBox-X window found. Start one with ./utils/dos-live.sh"
    exit 1
fi

eval "$(xdotool getwindowgeometry --shell "$WID")"   # sets X Y WIDTH HEIGHT

xdotool windowraise "$WID" 2>/dev/null
xdotool mousemove $((X + RX)) $((Y + RY))
sleep 0.2
xdotool click "$BTN"
