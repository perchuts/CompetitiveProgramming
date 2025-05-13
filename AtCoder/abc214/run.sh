#!/usr/bin/env zsh

ip="$HOME/cp/AtCoder/abc214/hin/in"
op="$HOME/cp/AtCoder/abc214/hin/out"
lixo="$HOME/cp/AtCoder/abc214/temp.txt"
g++ h.cpp -O2 -o h
for file in "$ip"/*;  do
	name=$(basename "$file")
	file2="$op/$name"
	echo "Processing: $file2"
	time ./h < "$file" > "$lixo"
	if (! cmp -s "$file2" "$lixo") then
		echo "deu ruim no caso $name"
	fi
done
