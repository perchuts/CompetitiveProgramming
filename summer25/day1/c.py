from fractions import Fraction
from math import lcm

n = int(input())
adj = [[] for i in range(n + 1)]
for i in range(1, n + 1):
	adj[i] = list(map(int, input().split(' ')))[1:]

val = [Fraction(0, 1) for i in range(n + 1)]
def check():
	for u in range(1, n+1):
		deg = len(adj[u])
		if deg == 0:
			continue

		a = val[u].numerator
		b = val[u].denominator * deg
		if a % b:
			return lcm(a, b) // a

		for v in adj[u]:
			val[v] += Fraction(a, b)
	
	return -1

val[1] = max(1, len(adj[1]))
while True:
	mx = check()
	if mx == -1:
		break
	val[1] *= mx
	for i in range(2, n+1):
		val[i] = 0

print(val[1])

