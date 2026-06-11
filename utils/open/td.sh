#!/usr/bin/env bash
# Open Turbo Debugger on the binary currently deployed in the demo dir.
# Unlike debug-x.sh this does NOT build or deploy anything - it just starts
# TD on C:\<TARGET>.EXE with the source paths set. Deploy first with
# ./utils/deploy.sh <TARGET> if you want to debug a fresh build.
#
# Usage:  ./utils/open/td.sh [TARGET]      TARGET := OPL | EDD  (default: EDD)
#
# MEMORY WARNING: real-mode TD + the symbol table live in the same 640 KB
# as the program. EDD's full startup needs more heap than that leaves and
# dies with exit code 203 (heap overflow) - breakpoints and source browsing
# work, but stepping through complete app init does not. For full-run
# debugging use the BP IDE instead: ./utils/open/bp.sh
#
# TD keys: F2 = breakpoint, F9 = run, F7/F8 = step into/over, Alt+X = quit.

set -u

TARGET="${1:-EDD}"

case "$TARGET" in
    OPL|EDD) ;;
    *) echo "Unknown target: $TARGET. Valid: OPL, EDD"; exit 1 ;;
esac

cd "$(dirname "$0")/../.." || exit 1

SD="-sdE:\\FDP\\$TARGET\\APP -sdL:\\UNIT -sdL:\\OOP -sdL:\\NET -sdL:\\L4"
SD="$SD -sdL:\\FDP -sdL:\\FRM"

exec dosbox-x -conf dosbox-x.conf -c "D:\\TD.EXE $SD C:\\$TARGET.EXE"
