import sys
from decimal import Decimal
import math
input = sys.stdin.readline

############ ---- Input Functions ---- ############
def inp():
    return(int(input()))
def inlt():
    return(list(map(int,input().split())))
def insr():
    s = input()
    return(list(s[:len(s) - 1]))
def invr():
    return(map(int,input().split()))


t = inp()

for i in range(t):
    [h1, h2, b] = invr()
    h1 = Decimal(math.log(Decimal(h1)))
    h2 = Decimal(math.log(Decimal(h2)))
    p = Decimal(math.log(Decimal(1.0) - Decimal(1.0)/Decimal(b)))
    x = Decimal((h2-h1)/p)
    print(math.ceil(x))

