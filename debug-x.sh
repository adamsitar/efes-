#!/usr/bin/env bash
# Launch DOSBox-X straight into Turbo Debugger with TARGET loaded and
# source paths set, ready to step (F7/F8). See TD-CHEATSHEET.md.
#
# Usage:  ./debug-x.sh [TARGET]
#   TARGET := OPL | EDD | FDA | SERVER   (default: OPL)
#
# OPL and EDD are debugged from the demo dir (C:) like OPL.BAT/EDD.BAT run
# them: the data files are seeded from INST\, then the debug build is
# copied over the EXE. Order matters — INST\ contains the shipped
# symbol-less EXEs, so seeding must happen BEFORE the debug build lands
# (this is also why running OPL.BAT after a manual swap un-swaps it).
# FDA and SERVER have no demo data, so they are loaded from their build
# dir on E: instead — good for stepping startup code until they go
# looking for data files.
#
# If TD runs out of memory, use the DPMI variant:  TD=TDX ./debug-x.sh OPL
#
# TD reads TDCONFIG.TD from its working directory; inside TD, Options >
# Save options persists preferences (e.g. display swapping) across runs.

set -u

TARGET="${1:-OPL}"
TD_BIN="${TD:-TD}"

case "$TARGET" in
    OPL)    FOLDER=OPL; INST=OPL ;;
    EDD)    FOLDER=EDD; INST=IDD ;;
    FDA)    FOLDER=FDA; INST= ;;
    SERVER) FOLDER=S;   INST= ;;
    *) echo "Unknown target: $TARGET. Valid: OPL, EDD, FDA, SERVER"; exit 1 ;;
esac

REPO_ROOT="$(cd "$(dirname "$0")" && pwd)"
cd "$REPO_ROOT"

BUILT_EXE="fdp.source/FDP/$FOLDER/APP/$TARGET.EXE"
DEMO_DIR="fdp.demo/idd"

if [[ ! -f "$BUILT_EXE" ]]; then
    echo "No built $TARGET.EXE - building it first..."
    ./build-headless.sh "$TARGET"
    [[ -f "$BUILT_EXE" ]] || { echo "Build failed; not launching TD."; exit 1; }
fi

if [[ -n "$INST" ]]; then
    if [[ ! -f "$DEMO_DIR/$TARGET.EXE.orig" && -f "$DEMO_DIR/$TARGET.EXE" ]]; then
        cp "$DEMO_DIR/$TARGET.EXE" "$DEMO_DIR/$TARGET.EXE.orig"
        echo "Backed up shipped $TARGET.EXE to $TARGET.EXE.orig"
    fi
    echo "Seeding demo data, swapping in debug build, launching TD..."
    dosbox-x -conf dosbox-x.conf \
        -c "copy C:\\INST\\$INST\\*.* C:\\ > NUL" \
        -c "copy E:\\FDP\\$FOLDER\\APP\\$TARGET.EXE C:\\ > NUL" \
        -c "D:\\$TD_BIN.EXE -sdE:\\FDP\\$FOLDER C:\\$TARGET.EXE"
else
    echo "$TARGET has no demo data; debugging in place on E:..."
    dosbox-x -conf dosbox-x.conf \
        -c "E:" \
        -c "cd \\FDP\\$FOLDER" \
        -c "D:\\$TD_BIN.EXE APP\\$TARGET.EXE"
fi
