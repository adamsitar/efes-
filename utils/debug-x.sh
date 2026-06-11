#!/usr/bin/env bash
# Open TARGET in Turbo Debugger: build if needed, put the debug EXE in the
# demo dir, launch DOSBox-X running TD on it. See TD-CHEATSHEET.md.
#
# Usage:  ./utils/debug-x.sh [TARGET]
#   TARGET := OPL | EDD | FDA | SERVER   (default: OPL)
#
# If TD runs out of memory, use the extended-memory variant:
#   TD=TD286 ./utils/debug-x.sh OPL

set -u

TARGET="${1:-OPL}"
TD_BIN="${TD:-TD}"

case "$TARGET" in
    OPL)    FOLDER=OPL; DEMO=yes ;;
    EDD)    FOLDER=EDD; DEMO=yes ;;
    FDA)    FOLDER=FDA; DEMO= ;;   # no demo data: debugged in place on E:
    SERVER) FOLDER=S;   DEMO= ;;
    *) echo "Unknown target: $TARGET. Valid: OPL, EDD, FDA, SERVER"; exit 1 ;;
esac

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$REPO_ROOT"

BUILT="fdp.source/FDP/$FOLDER/APP/$TARGET.EXE"
DEMO_DIR="fdp.demo/idd"

[[ -f "$BUILT" ]] || ./utils/build-headless.sh "$TARGET"
[[ -f "$BUILT" ]] || { echo "Build failed; not launching TD."; exit 1; }

# Units and includes are recorded in the debug info by bare filename, so TD
# needs the list of folders to search for them. L: is mounted at E:\FDP\LIB
# to keep this under the DOS command-line length limit.
SD="-sdE:\\FDP\\$FOLDER\\APP -sdL:\\UNIT -sdL:\\OOP -sdL:\\NET -sdL:\\L4"
SD="$SD -sdL:\\FDP -sdL:\\FRM -sdL:\\MNU -sdL:\\ARCH"

if [[ -n "$DEMO" ]]; then
    # Debug from C:\ so the program finds its data files. Back up the
    # shipped EXE once, then put the debug build in its place. (Don't run
    # OPL.BAT/EDD.BAT afterwards - they restore the shipped EXE from INST\.)
    if [[ -f "$DEMO_DIR/$TARGET.EXE" && ! -f "$DEMO_DIR/$TARGET.EXE.orig" ]]; then
        cp "$DEMO_DIR/$TARGET.EXE" "$DEMO_DIR/$TARGET.EXE.orig"
    fi
    # The programs are overlaid: the EXE and its .OVR are a matched pair
    # from the same compile. Deploying only the EXE against an older OVR
    # fails at startup with "Overlay manager error (-1)".
    cp "$BUILT" "${BUILT%.EXE}.OVR" "$DEMO_DIR/"
    dosbox-x -conf dosbox-x.conf -c "D:\\$TD_BIN.EXE $SD C:\\$TARGET.EXE"
else
    dosbox-x -conf dosbox-x.conf \
        -c "E:" -c "cd \\FDP\\$FOLDER\\APP" \
        -c "D:\\$TD_BIN.EXE $SD $TARGET.EXE"
fi
