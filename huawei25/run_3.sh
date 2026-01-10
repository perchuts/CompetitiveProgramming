#!/usr/bin/env bash
P=sa2
g++ ${P}.cpp -Ofast -o ${P} || exit 1
./${P} < secret/01 > out_a2/01.out
cat secret/01 out_a2/01.out > check_a2/01.out
echo "ok 01"
./${P} < secret/02 > out_a2/02.out
cat secret/02 out_a2/02.out > check_a2/02.out
echo "ok 02"
#./${P} < secret/03 > out_a2/03.out
#cat secret/03 out_a2/03.out > check_a2/03.out
#echo "ok 03"
#./${P} < secret/04 > out_a2/04.out
#cat secret/04 out_a2/04.out > check_a2/04.out
#echo "ok 04"
#./${P} < secret/05 > out_a2/05.out
#cat secret/05 out_a2/05.out > check_a2/05.out
#echo "ok 05"
echo "now running get_score..."
./check_3.sh
