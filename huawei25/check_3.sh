#!/usr/bin/env bash
P=get_score
g++ ${P}.cpp -Ofast -o ${P} || exit 1
./${P} < check_a2/01.out
./${P} < check_a2/02.out
#./${P} < check_a2/03.out
#./${P} < check_a2/04.out
#./${P} < check_a2/05.out
