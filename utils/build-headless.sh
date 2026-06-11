#!/usr/bin/env bash
# Headless BPC build harness under DOSBox-X.
#
# Usage:  ./utils/build-headless.sh [TARGET]
#   TARGET := OPL | EDD | FDA | SERVER   (default: OPL)
#
# Invokes E:\BUILD.BAT inside DOSBox-X, which redirects compiler output to
# E:\COMPILE.LOG (= fdp.source/COMPILE.LOG on the host). Runs fully headless
# (dummy SDL video driver): no window appears.

set -u

TARGET="${1:-OPL}"

# Map target name → (subfolder under FDP, main program file)
case "$TARGET" in
    OPL)    FOLDER=OPL; PROGRAM=OPL ;;
    EDD)    FOLDER=EDD; PROGRAM=EDD ;;
    FDA)    FOLDER=FDA; PROGRAM=FDA ;;
    SERVER) FOLDER=S;   PROGRAM=SERVER ;;
    *) echo "Unknown target: $TARGET. Valid: OPL, EDD, FDA, SERVER"; exit 1 ;;
esac

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SRC_DIR="$REPO_ROOT/fdp.source"
LOG_HOST="$SRC_DIR/COMPILE.LOG"
EXE_HOST="$SRC_DIR/FDP/$FOLDER/APP/$PROGRAM.EXE"

# Wipe previous artifacts so we can unambiguously tell what this run produced.
rm -f "$LOG_HOST" "$EXE_HOST"

echo "Building target: $TARGET  (folder=\\FDP\\$FOLDER, program=$PROGRAM.PAS)"

# The conf mounts drives via relative paths, so run from the repo root.
cd "$REPO_ROOT"
SDL_VIDEODRIVER=dummy timeout -k 5 120 \
    dosbox-x -conf dosbox-x.conf -c "E:\\BUILD.BAT $FOLDER $PROGRAM" -exit \
    > /dev/null 2>&1
[[ $? -eq 124 ]] && echo "WARNING: build session hung; killed after 120 s"

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
    echo "SUCCESS: $TARGET.EXE produced at $EXE_HOST ($(stat -c%s "$EXE_HOST") bytes)"
else
    echo "FAILED: $TARGET.EXE not produced"
fi
