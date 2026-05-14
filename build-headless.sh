#!/usr/bin/env bash
# Headless OPL build under DOSBox-X.
# Invokes E:\BUILD.BAT inside the emulated DOS environment, which captures
# BPC output to E:\COMPILE.LOG (= fdp.source/COMPILE.LOG on the host).

set -u

REPO_ROOT="$(cd "$(dirname "$0")" && pwd)"
SRC_DIR="$REPO_ROOT/fdp.source"
LOG_HOST="$SRC_DIR/COMPILE.LOG"
EXE_HOST="$SRC_DIR/FDP/OPL/APP/OPL.EXE"

# Wipe previous artifacts so we can unambiguously tell what this run produced.
rm -f "$LOG_HOST" "$EXE_HOST"

dosbox-x -conf "$REPO_ROOT/dosbox-x.conf" -c "E:\\BUILD.BAT" -exit

echo
echo "--- build-headless.sh: dosbox-x exited ---"
if [[ -s "$LOG_HOST" ]]; then
    echo "Log: $LOG_HOST  ($(wc -l < "$LOG_HOST") lines)"
    echo "Last 20 lines:"
    tail -20 "$LOG_HOST"
else
    echo "WARNING: no log produced at $LOG_HOST"
fi
echo
if [[ -f "$EXE_HOST" ]]; then
    echo "SUCCESS: OPL.EXE produced at $EXE_HOST"
else
    echo "FAILED: OPL.EXE not produced"
fi
