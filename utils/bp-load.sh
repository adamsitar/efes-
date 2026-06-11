#!/usr/bin/env bash
# Load breakpoints from a text file into the RUNNING Borland Pascal IDE.
# Edit the file in your normal editor (neovim), then run this; no clicking
# around inside the IDE needed.
#
# Usage:  ./utils/bp-load.sh [FILE]        (default: breakpoints.txt)
#
# File format - one breakpoint per line, '#' comments and blanks ignored:
#   <dos-file-path> <line-number> [condition...]
# Example:
#   E:\FDP\EDD\APP\EDD.PAS 37
#   E:\FDP\EDD\APP\AP.PAS  152  pocet > 10
#
# Requirements & caveats:
#   - A live IDE session must be open and idle in the editor
#     (./utils/open/bp.sh EDD or ./utils/dos-live.sh 'D:\BP.EXE ...').
#   - Keep hands off keyboard/mouse while it runs (XTEST injection; see
#     keys.sh). Each breakpoint takes ~10 s.
#   - Breakpoints only bind in modules compiled with debug info: EDD.PAS
#     and AP.PAS carry {$D+,L+}; add the same directive to other units
#     (right after their {$I comp.h}) and rebuild to break inside them.
#   - The line must hold executable code, or the IDE will complain when
#     the program runs.
#   - Verify afterwards: Debug -> Breakpoints lists everything, or
#     ./utils/screenshot.sh and look for red lines.
#
# Mechanism: drives Debug -> Add breakpoint... (alt+d, p) and fills the
# dialog: Condition [Tab] Pass count [Tab] File name [Tab] Line number,
# then Return = OK. Tabbing into a Borland input field selects its content,
# so typing replaces the prefilled value.

set -u

BPFILE="${1:-breakpoints.txt}"
REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$REPO_ROOT"
KEYS="$REPO_ROOT/utils/keys.sh"

[[ -f "$BPFILE" ]] || { echo "No such file: $BPFILE"; exit 1; }
xdotool search --name 'DOSBox-X' >/dev/null 2>&1 || {
    echo "No DOSBox-X window. Start the IDE first: ./utils/open/bp.sh EDD"; exit 1; }

N=0
while read -r FILE LINE COND; do
    [[ -z "${FILE:-}" || "${FILE:0:1}" == "#" ]] && continue
    if ! [[ "${LINE:-}" =~ ^[0-9]+$ ]]; then
        echo "SKIP malformed line (need: FILE LINENUM [condition]): $FILE ${LINE:-}"
        continue
    fi

    echo "Setting breakpoint: $FILE:$LINE ${COND:+if $COND}"

    # Debug menu -> Add breakpoint...
    "$KEYS" alt+d || exit 1
    sleep 0.4
    "$KEYS" p || exit 1
    sleep 0.8

    # Condition field (focused). Type condition if any, else leave empty.
    if [[ -n "${COND:-}" ]]; then
        "$KEYS" --type "$COND" || exit 1
    fi
    # -> Pass count (leave) -> File name (replace) -> Line number (replace)
    "$KEYS" Tab Tab || exit 1
    "$KEYS" --type "$FILE" || exit 1
    "$KEYS" Tab || exit 1
    "$KEYS" --type "$LINE" Return || exit 1
    sleep 0.6
    N=$((N+1))
done < "$BPFILE"

echo "Done: $N breakpoint(s) sent. Verify via Debug -> Breakpoints or ./utils/screenshot.sh"
