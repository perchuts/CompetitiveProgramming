#!/usr/bin/env bash
set -euo pipefail

if [ $# -ne 1 ]; then
  echo "Usage: $0 sol.cpp"
  exit 1
fi

src="$1"
tests_dir="tests"
out_dir="out"
bin="./sol_bin"

mkdir -p "$out_dir"

g++ -std=c++17 -O2 -o "$bin" "$src"

for f in "$tests_dir"/*; do
  [ -f "$f" ] || continue
  name="$(basename "$f")"
  "$bin" < "$f" > "$out_dir/$name.out"
done
