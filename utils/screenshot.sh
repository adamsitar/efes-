#!/usr/bin/env bash
# Capture the running DOSBox-X window to a PNG and print its path.
# This is how the agent "sees the screen" of a live session (dos-live.sh) -
# the FDP programs and TD are graphics/text-mode and never write to stdout.
#
# Usage:  ./utils/screenshot.sh [OUTPUT.png]     (default /tmp/dosbox-screen.png)
#
# Captures by X window id (works under WSLg's rootless XWayland, where
# grabbing root-window coordinates returns black).

set -u

OUT="${1:-/tmp/dosbox-screen.png}"

WID="$(xdotool search --name 'DOSBox-X' 2>/dev/null | head -1)"
if [[ -z "$WID" ]]; then
    echo "No DOSBox-X window found. Start one with ./utils/dos-live.sh"
    exit 1
fi

# ffmpeg emits a harmless one-shot SHM "Cannot get the image data" warning
# under WSLg; keep stderr out of the way and surface it only on real failure.
if ! ffmpeg -y -loglevel error -f x11grab -window_id "$WID" \
        -i "${DISPLAY:-:0}" -frames:v 1 "$OUT" 2>/tmp/dosbox-screenshot.err \
        || [[ ! -s "$OUT" ]]; then
    echo "Screenshot failed:"
    cat /tmp/dosbox-screenshot.err
    exit 1
fi

echo "$OUT"
