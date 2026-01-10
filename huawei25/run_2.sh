#!/usr/bin/env bash
P=sa
g++ ${P}.cpp -Ofast -o ${P} || exit 1
./${P} < tests/01 > out_a1/01.out
cat tests/01 out_a1/01.out > check_a1/01.out
echo "ok 01"
./${P} < tests/02 > out_a1/02.out
cat tests/02 out_a1/02.out > check_a1/02.out
echo "ok 02"
./${P} < tests/03 > out_a1/03.out
cat tests/03 out_a1/03.out > check_a1/03.out
echo "ok 03"
echo "now running get_score for first three tries..."
./check_2.sh
