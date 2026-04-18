#!/usr/bin/env bash
set -euo pipefail

out_dir="out"

if [ ! -d "$out_dir" ]; then
  echo "Folder '$out_dir' not found."
  exit 1
fi

for f in "$out_dir"/*.out; do
  [ -f "$f" ] || continue
  name="$(basename "$f" .out)"
  echo "===== $name ====="
  cat "$f"
  echo
done
