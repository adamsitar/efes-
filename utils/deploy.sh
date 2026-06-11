#!/usr/bin/env bash
# Deploy a binary pair (EXE + OVR, matched from one compile) into the demo
# dir. The two files MUST come from the same build - a fresh EXE against an
# older OVR dies at startup with "Overlay manager error (-1)".
#
# Usage:  ./utils/deploy.sh EDD            deploy the self-built debug pair
#         ./utils/deploy.sh EDD --shipped  restore the shipped 1999 pair
#
# Targets with demo data: EDD (config set INST\IDD), OPL (INST\OPL).
# Remember: seeding a config set (copy C:\INST\IDD\*.* C:\) also overwrites
# the binaries with shipped ones - re-run this script afterwards.

set -u

TARGET="${1:-}"
MODE="${2:-build}"

case "$TARGET" in
    EDD) INST=IDD ;;
    OPL) INST=OPL ;;
    *) echo "Usage: $0 EDD|OPL [--shipped]"; exit 1 ;;
esac

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$REPO_ROOT"

DEMO_DIR="fdp.demo/idd"

if [[ "$MODE" == "--shipped" ]]; then
    SRC_DIR="$DEMO_DIR/INST/$INST"
    LABEL="shipped 1999"
else
    SRC_DIR="fdp.source/FDP/$TARGET/APP"
    LABEL="self-built"
fi

EXE="$SRC_DIR/$TARGET.EXE"
OVR="$SRC_DIR/$TARGET.OVR"

[[ -f "$EXE" && -f "$OVR" ]] || { echo "Missing $EXE or $OVR - build first (./utils/build-headless.sh $TARGET)?"; exit 1; }

cp "$EXE" "$OVR" "$DEMO_DIR/"
echo "Deployed $LABEL $TARGET pair to $DEMO_DIR/:"
echo "  $TARGET.EXE  $(stat -c%s "$DEMO_DIR/$TARGET.EXE") bytes"
echo "  $TARGET.OVR  $(stat -c%s "$DEMO_DIR/$TARGET.OVR") bytes"
