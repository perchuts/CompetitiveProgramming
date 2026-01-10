#!/usr/bin/env bash
P=get_score
g++ ${P}.cpp -Ofast -o ${P} || exit 1
./${P} < check_a1/01.out
./${P} < check_a1/02.out
./${P} < check_a1/03.out
