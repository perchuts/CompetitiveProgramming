#!/usr/bin/env bash
P=generator
g++ ${P}.cpp -Ofast -o ${P} || exit 1
./${P} 69420 > secret/01
./${P} 69420 > secret/02
./${P} 69420 > secret/03
./${P} 69420 > secret/04
./${P} 69420 > secret/05
