#!/usr/bin/env bash
# Open the Borland Pascal 7 IDE (BP.EXE) with a program's main source loaded.
# This is the original author's likely debug workflow: the IDE runs in DPMI
# protected mode, so the IDE + debug info live in extended memory and the
# real-mode program being debugged keeps (nearly) the whole 640 KB - the
# thing standalone real-mode TD cannot do (heap overflow, exit code 203).
#
# Usage:  ./utils/open/bp.sh [TARGET]      TARGET := OPL | EDD | FDA | SERVER
#                                          (default: EDD)
#
# Inside the IDE: F9 = compile (same compiler engine as BPC; same EXE/OVR
# written to disk), F7/F8 = step into/over, F4 = run to cursor,
# Ctrl+F8 = toggle breakpoint, Ctrl+F9 = run, Alt+X = quit.
#
# The IDE starts with cwd C:\ (demo dir) so the debugged program finds its
# data files, and so the IDE picks up C:\BP.TP - the saved per-project
# options (unit/include/EXE directories matching BPC.CFG). If that file is
# missing, set Options -> Directories by hand and Options -> Save.

set -u

TARGET="${1:-EDD}"

case "$TARGET" in
    OPL)    SRC='E:\FDP\OPL\APP\OPL.PAS' ;;
    EDD)    SRC='E:\FDP\EDD\APP\EDD.PAS' ;;
    FDA)    SRC='E:\FDP\FDA\APP\FDA.PAS' ;;
    SERVER) SRC='E:\FDP\S\APP\SERVER.PAS' ;;
    *) echo "Unknown target: $TARGET. Valid: OPL, EDD, FDA, SERVER"; exit 1 ;;
esac

cd "$(dirname "$0")/../.." || exit 1
exec dosbox-x -conf dosbox-x.conf -c "D:\\BP.EXE $SRC"
