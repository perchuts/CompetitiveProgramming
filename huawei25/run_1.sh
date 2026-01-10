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
./${P} < tests/04 > out_a1/04.out
cat tests/04 out_a1/04.out > check_a1/04.out
echo "ok 04"
./${P} < tests/05 > out_a1/05.out
cat tests/05 out_a1/05.out > check_a1/05.out
echo "ok 05"
./${P} < tests/06 > out_a1/06.out
cat tests/06 out_a1/06.out > check_a1/06.out
echo "ok 06"
./${P} < tests/07 > out_a1/07.out
cat tests/07 out_a1/07.out > check_a1/07.out
echo "ok 07"
./${P} < tests/08 > out_a1/08.out
cat tests/08 out_a1/08.out > check_a1/08.out
echo "ok 08"
./${P} < tests/09 > out_a1/09.out
cat tests/09 out_a1/09.out > check_a1/09.out
echo "ok 09"
./${P} < tests/10 > out_a1/10.out
cat tests/10 out_a1/10.out > check_a1/10.out
echo "ok 10"
echo "now running get_score for all tries..."
./check_1.sh
