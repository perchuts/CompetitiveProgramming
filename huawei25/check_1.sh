#!/usr/bin/env bash
P=get_score
g++ ${P}.cpp -Ofast -o ${P} || exit 1
./${P} < check_a1/01.out
./${P} < check_a1/02.out
./${P} < check_a1/03.out
./${P} < check_a1/04.out
./${P} < check_a1/05.out
./${P} < check_a1/06.out
./${P} < check_a1/07.out
./${P} < check_a1/08.out
./${P} < check_a1/09.out
./${P} < check_a1/10.out
