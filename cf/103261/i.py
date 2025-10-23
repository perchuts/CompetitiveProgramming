from math import gcd
d, k = map(int, input().split(' '))


g = gcd(d, k)
for i in range(340):
    g = gcd(k, g*g)


if d % 4 == 2 and k % 2 == 0 and k > 2:
    g *= 2

print(d*g)

