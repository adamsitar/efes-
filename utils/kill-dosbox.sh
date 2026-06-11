#!/usr/bin/env bash
# Kill every running DOSBox-X instance. Run this whenever a session is left
# behind (agent forgot to clean up, build hung, window unresponsive).
#
# Usage:  ./utils/kill-dosbox.sh

# -x matches the exact process name only; -f patterns would also match an
# unrelated shell whose command line merely mentions dosbox-x (and kill it).
N="$(pgrep -c -x 'dosbox-x' 2>/dev/null || true)"
if [[ -z "$N" || "$N" -eq 0 ]]; then
    echo "No DOSBox-X instances running."
else
    pkill -x 'dosbox-x'
    sleep 1
    pkill -9 -x 'dosbox-x' 2>/dev/null
    echo "Killed $N DOSBox-X instance(s)."
fi
rm -f /tmp/dosbox-live.pid
