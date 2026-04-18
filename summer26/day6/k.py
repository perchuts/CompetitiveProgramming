

L = []
for i in range(9):
    L.append([])
    for j in range(9):
        L[i].append(0)


def f(i,j,k):
    if k == 9:
        for a in range(9):
            for b in range(9):
                print(L[a][b],end=' ')
            print()
        print()
    if i >= 9:
        return
    # tentar colocar a rainha na pos (i,j)
    ok = 1
    for a in range(9):
        if L[i][a]:
            ok = 0
    for b in range(9):
        if L[b][j]:
            ok = 0
    for c in range(-10,10):
        ni = i+c
        nj = j+c
        if min(ni, nj) >= 0 and max(ni, nj) < 9:
            if L[ni][nj]:
                ok = 0
    for c in range(-10,10):
        ni = i+c
        nj = j-c
        if min(ni, nj) >= 0 and max(ni, nj) < 9:
            if L[ni][nj]:
                ok = 0
    pi = i
    pj = j+1
    if pj == 9:
        pj = 0
        pi += 1
    if not ok:
        f(pi,pj,k)
        return
    L[i][j] = 1
    f(pi,pj,k+1)
    L[i][j] = 0
    f(pi,pj,k)

f(0,0,0)
    



