#!/usr/bin/env bash
# Run DOS commands headlessly in DOSBox-X and print their captured output.
#
# Usage:  ./utils/dos.sh 'DIR C:\' 'TYPE C:\ERR.LOG'
#   Each argument is one DOS command, executed in order with cwd C:\.
#   Commands without an explicit redirect get their stdout appended to
#   E:\AGENT.LOG (= fdp.source/AGENT.LOG on the host), which is printed here
#   when the session ends.
#
# Caveats:
#   - Graphics-mode programs (EDD, OPL, TD) draw on the screen, not stdout;
#     a redirect captures nothing. Use dos-live.sh + screenshot.sh for those.
#   - The session is killed after DOS_TIMEOUT seconds (default 60). A timeout
#     usually means a program reached its interactive UI - that can be the
#     liveness signal you wanted, but you won't see its screen this way.
#
# Env: DOS_TIMEOUT  seconds before the session is killed (default 60).

set -u

if [[ $# -eq 0 ]]; then
    echo "Usage: $0 'DOS COMMAND' ['DOS COMMAND' ...]"
    exit 1
fi

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$REPO_ROOT"

LOG_HOST="fdp.source/AGENT.LOG"
rm -f "$LOG_HOST"

ARGS=()
for CMD in "$@"; do
    case "$CMD" in
        *">"*) ARGS+=(-c "$CMD") ;;                      # caller redirects
        *)     ARGS+=(-c "$CMD >> E:\\AGENT.LOG") ;;
    esac
done

SDL_VIDEODRIVER=dummy timeout -k 5 "${DOS_TIMEOUT:-60}" \
    dosbox-x -conf dosbox-x.conf "${ARGS[@]}" -exit > /dev/null 2>&1
RC=$?

[[ $RC -eq 124 ]] && echo "[dos.sh] session killed after ${DOS_TIMEOUT:-60}s timeout (program hung or reached interactive UI)"

if [[ -s "$LOG_HOST" ]]; then
    tr -d '\r' < "$LOG_HOST"
else
    echo "[dos.sh] no output captured in $LOG_HOST"
fi
