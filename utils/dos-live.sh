#!/usr/bin/env bash
# Start a live DOSBox-X session in the background (real window) and return.
# This is the agent's way to run interactive/graphics programs: start the
# session, then observe with screenshot.sh, drive with keys.sh, and clean up
# with kill-dosbox.sh.
#
# Usage:  ./utils/dos-live.sh [CMD ...]
#   Each argument is one DOS command run at startup (cwd C:\).
#   No arguments = plain session sitting at the C:\> prompt.
#
# Examples:
#   ./utils/dos-live.sh                       # just the prompt
#   ./utils/dos-live.sh EDD                   # run EDD, watch via screenshot.sh
#   ./utils/dos-live.sh 'D:\TD.EXE C:\EDD.EXE'
#
# Prints the DOSBox PID and X window id. Only one live session at a time.

set -u

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$REPO_ROOT"

PIDFILE=/tmp/dosbox-live.pid

if [[ -f "$PIDFILE" ]] && kill -0 "$(cat "$PIDFILE")" 2>/dev/null; then
    echo "A live session is already running (PID $(cat "$PIDFILE"))."
    echo "Kill it first: ./utils/kill-dosbox.sh"
    exit 1
fi

ARGS=()
for CMD in "$@"; do
    ARGS+=(-c "$CMD")
done

# output=surface (not opengl): XGetImage can only read CPU-side surfaces,
# so screenshot.sh would get a tiny stale buffer under the GL renderer.
# usescancodes=false: raw X keycode translation garbles/drops the synthetic
# key events keys.sh sends; keysym mode matches what xdotool emits.
# autolock=false: otherwise the first synthetic click CAPTURES the mouse
# (relative-motion mode), breaking click.sh's absolute coordinates.
setsid dosbox-x -conf dosbox-x.conf \
    -set "sdl output=surface" -set "sdl usescancodes=false" \
    -set "sdl autolock=false" \
    ${ARGS+"${ARGS[@]}"} \
    > /tmp/dosbox-live.log 2>&1 &
PID=$!
echo "$PID" > "$PIDFILE"

# Wait for the window to appear so screenshot.sh/keys.sh work immediately.
WID=
for _ in $(seq 1 50); do
    WID="$(xdotool search --name 'DOSBox-X' 2>/dev/null | head -1)"
    [[ -n "$WID" ]] && break
    kill -0 "$PID" 2>/dev/null || { echo "DOSBox-X died at startup; see /tmp/dosbox-live.log"; rm -f "$PIDFILE"; exit 1; }
    sleep 0.2
done

echo "Live session started: PID=$PID window=$WID"
echo "Observe: ./utils/screenshot.sh   Drive: ./utils/keys.sh   Stop: ./utils/kill-dosbox.sh"
