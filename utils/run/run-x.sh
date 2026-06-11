#!/usr/bin/env bash
# Launch DOSBox-X interactively. The conf mounts drives via relative
# paths, so run from the repo root regardless of where this is called from.
cd "$(dirname "$0")/../.." || exit 1
exec dosbox-x -conf dosbox-x.conf
