#!/usr/bin/env bash
# Show the FDP logs from the host side.
#
# Usage:  ./utils/logs.sh [err|compile|agent|all]      (default: all)
#         ./utils/logs.sh err --clear
#
#   err      C:\ERR.LOG - the programs append their startup-failure reasons
#            here. GOTCHA: seeding config from INST\ plants a 1998-dated
#            ERR.LOG from the original author's machine; only lines dated
#            today are from your run. Use '--clear' before reproducing a
#            failure so everything you then see is fresh.
#   compile  E:\COMPILE.LOG - BPC compiler output from the last build.
#   agent    E:\AGENT.LOG - output captured by the last dos.sh run.

set -u

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$REPO_ROOT"

WHAT="${1:-all}"

show_err() {
    local F="fdp.demo/idd/ERR.LOG"
    if [[ "${2:-}" == "--clear" || "${1:-}" == "--clear" ]]; then
        rm -f "$F"
        echo "ERR.LOG cleared. Lines appearing after the next run are all fresh."
        return
    fi
    if [[ -f "$F" ]]; then
        echo "=== ERR.LOG (modified: $(stat -c '%y' "$F" | cut -d. -f1)) ==="
        echo "    (trust only lines dated today - older ones are stale seed data)"
        tr -d '\r' < "$F"
    else
        echo "=== ERR.LOG: does not exist (no failure logged since last clear) ==="
    fi
}

show_compile() {
    local F="fdp.source/COMPILE.LOG"
    if [[ -s "$F" ]]; then
        echo "=== COMPILE.LOG (last 25 lines) ==="
        tail -25 "$F" | tr -d '\r'
    else
        echo "=== COMPILE.LOG: missing or empty ==="
    fi
}

show_agent() {
    local F="fdp.source/AGENT.LOG"
    if [[ -s "$F" ]]; then
        echo "=== AGENT.LOG (last dos.sh output) ==="
        tr -d '\r' < "$F"
    else
        echo "=== AGENT.LOG: missing or empty ==="
    fi
}

case "$WHAT" in
    err)     show_err "${2:-}" ;;
    compile) show_compile ;;
    agent)   show_agent ;;
    all)     show_err; echo; show_compile; echo; show_agent ;;
    *) echo "Usage: $0 [err|compile|agent|all] [--clear]"; exit 1 ;;
esac
