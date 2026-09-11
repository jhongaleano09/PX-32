#!/usr/bin/env bash
set -euo pipefail
ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
STUB_DIR="$ROOT_DIR/scripts/arduino-stubs"
count=0
while IFS= read -r sketch; do
  c++ -std=c++17 -fsyntax-only -x c++ -I "$STUB_DIR" -include "$STUB_DIR/Arduino.h" "$sketch"
  count=$((count+1))
done < <(find "$ROOT_DIR/code/educational" -mindepth 2 -name '*.ino' -type f | sort)
printf 'OK: %d sketches superan la comprobación sintáctica con stubs Arduino.\n' "$count"
