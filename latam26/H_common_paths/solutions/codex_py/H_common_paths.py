import sys

MOD = 998244353
ROOT = 3
MAX_LOG = 20
SMALL_MUL = 96


def ints_from_stdin():
    data = sys.stdin.buffer.read()
    num = 0
    in_num = False
    for b in data:
        if 48 <= b <= 57:
            num = num * 10 + (b - 48)
            in_num = True
        elif in_num:
            yield num
            num = 0
            in_num = False
    if in_num:
        yield num


ROOTS = [0] * (MAX_LOG + 1)
IROOTS = [0] * (MAX_LOG + 1)
INV_POW2 = [0] * (MAX_LOG + 1)
WPOW = [None] * (MAX_LOG + 1)
IWPOW = [None] * (MAX_LOG + 1)
for level in range(1, MAX_LOG + 1):
    length = 1 << level
    ROOTS[level] = pow(ROOT, (MOD - 1) // length, MOD)
    IROOTS[level] = pow(ROOTS[level], MOD - 2, MOD)
    INV_POW2[level] = pow(length, MOD - 2, MOD)
    half = length >> 1

    ws = [0] * half
    iws = [0] * half

    w = 1
    iw = 1
    i = 0
    while i < half:
        ws[i] = w
        iws[i] = iw
        w = (w * ROOTS[level]) % MOD
        iw = (iw * IROOTS[level]) % MOD
        i += 1

    WPOW[level] = ws
    IWPOW[level] = iws


def ntt(a, invert):
    n = len(a)

    j = 0
    i = 1
    while i < n:
        bit = n >> 1
        while j & bit:
            j ^= bit
            bit >>= 1
        j ^= bit
        if i < j:
            a[i], a[j] = a[j], a[i]
        i += 1

    length = 2
    level = 1
    while length <= n:
        pows = IWPOW[level] if invert else WPOW[level]
        half = length >> 1

        start = 0
        while start < n:
            left = start
            right = start + half
            limit = start + half
            pw = 0
            while left < limit:
                w = pows[pw]
                u = a[left]
                v = (a[right] * w) % MOD

                x = u + v
                if x >= MOD:
                    x -= MOD
                y = u - v
                if y < 0:
                    y += MOD

                a[left] = x
                a[right] = y

                left += 1
                right += 1
                pw += 1

            start += length

        length <<= 1
        level += 1

    if invert:
        inv_n = INV_POW2[n.bit_length() - 1]
        i = 0
        while i < n:
            a[i] = (a[i] * inv_n) % MOD
            i += 1


def multiply(a, b):
    if not a or not b:
        return []

    la = len(a)
    lb = len(b)
    if la < lb:
        a, b = b, a
        la, lb = lb, la

    if lb == 1:
        c = b[0]
        return [(x * c) % MOD for x in a]

    # Small convolutions are faster without NTT in Python.
    if lb <= SMALL_MUL:
        res = [0] * (la + lb - 1)
        i = 0
        while i < la:
            ai = a[i]
            if ai:
                j = 0
                while j < lb:
                    res[i + j] = (res[i + j] + ai * b[j]) % MOD
                    j += 1
            i += 1
        return res

    need = la + lb - 1
    n = 1
    while n < need:
        n <<= 1

    fa = a + [0] * (n - la)
    fb = b + [0] * (n - lb)

    ntt(fa, False)
    ntt(fb, False)

    i = 0
    while i < n:
        fa[i] = (fa[i] * fb[i]) % MOD
        i += 1

    ntt(fa, True)
    del fa[need:]
    return fa


def add_poly(p, q):
    lp = len(p)
    lq = len(q)
    if lp < lq:
        p.extend([0] * (lq - lp))
    i = 0
    while i < lq:
        p[i] += q[i]
        if p[i] >= MOD:
            p[i] -= MOD
        i += 1


def add_scaled_poly(p, q, c):
    lp = len(p)
    lq = len(q)
    if lp < lq:
        p.extend([0] * (lq - lp))
    i = 0
    while i < lq:
        p[i] = (p[i] + q[i] * c) % MOD
        i += 1


it = iter(ints_from_stdin())
n = next(it)
m = n - 1

head = [-1] * n
to = [0] * (2 * m)
nxt = [0] * (2 * m)
edge_ptr = 0


def add_edge(u, v):
    global edge_ptr
    to[edge_ptr] = v
    nxt[edge_ptr] = head[u]
    head[u] = edge_ptr
    edge_ptr += 1


for _ in range(m):
    u = next(it) - 1
    v = next(it) - 1
    add_edge(u, v)
    add_edge(v, u)

tk = [0] * n
subt = [0] * n
dep = [0] * n
szt = [0] * n
par0 = [0] * n
comp_par = [0] * n
seen = [0] * n
stamp = 1

stack_node = [0] * n
stack_par = [0] * n
stack_depth = [0] * n
order = [0] * n


def precalc():
    top = 0
    ord_sz = 0

    stack_node[top] = 0
    top += 1
    par0[0] = -1
    dep[0] = 0

    while top:
        top -= 1
        u = stack_node[top]
        order[ord_sz] = u
        ord_sz += 1

        e = head[u]
        pu = par0[u]
        while e != -1:
            v = to[e]
            if v != pu:
                par0[v] = u
                dep[v] = dep[u] + 1
                stack_node[top] = v
                top += 1
            e = nxt[e]

    i = ord_sz - 1
    while i >= 0:
        u = order[i]
        s = 1
        e = head[u]
        while e != -1:
            v = to[e]
            if par0[v] == u:
                s += subt[v]
            e = nxt[e]
        subt[u] = s
        i -= 1


def process_subtree(start, root, pol):
    top = 0
    stack_node[top] = start
    stack_par[top] = root
    stack_depth[top] = 1
    top += 1

    while top:
        top -= 1
        u = stack_node[top]
        p = stack_par[top]
        d = stack_depth[top]

        tot = 0
        acum = 1

        e = head[u]
        while e != -1:
            v = to[e]
            if v != p:
                if dep[v] < dep[u]:
                    dir_sz = n - subt[u]
                else:
                    dir_sz = subt[v]
                tot += (dir_sz * acum) % MOD
                if tot >= MOD:
                    tot -= MOD
                acum += dir_sz
                if acum >= MOD:
                    acum -= MOD

                if tk[v] == 0:
                    stack_node[top] = v
                    stack_par[top] = u
                    stack_depth[top] = d + 1
                    top += 1
            e = nxt[e]

        tot = (2 * tot + 1) % MOD

        if len(pol) <= d:
            pol.extend([0] * (d + 1 - len(pol)))
        val = pol[d] + tot
        if val >= MOD:
            val -= MOD
        pol[d] = val


def process_root(rt):
    pols = []
    sizes = []

    e = head[rt]
    while e != -1:
        x = to[e]
        if dep[x] < dep[rt]:
            sx = n - subt[rt]
        else:
            sx = subt[x]
        sizes.append(sx)

        now = []
        if tk[x] == 0:
            process_subtree(x, rt, now)
        pols.append(now)
        e = nxt[e]

    k = len(pols)

    if k > 1:
        idxs = list(range(k))
        idxs.sort(key=lambda i: len(pols[i]))
        pols = [pols[i] for i in idxs]
        sizes = [sizes[i] for i in idxs]

    # Sum over all i < j of pols[i] * pols[j], processed from smaller to larger.
    ans = []
    acc = []
    i = 0
    while i < k:
        pi = pols[i]
        if acc and pi:
            cur = multiply(acc, pi)
            add_poly(ans, cur)
        add_poly(acc, pi)
        i += 1

    sum_sizes = 0
    sum_sq_sizes = 0
    i = 0
    while i < k:
        s = sizes[i]
        sum_sizes += s
        if sum_sizes >= MOD:
            sum_sizes -= MOD
        sum_sq_sizes += (s * s) % MOD
        if sum_sq_sizes >= MOD:
            sum_sq_sizes -= MOD
        i += 1

    i = 0
    while i < k:
        s = sizes[i]

        tot = (2 * (n - s - 1)) % MOD
        tot += 1
        if tot >= MOD:
            tot -= MOD

        other = sum_sizes - s
        if other < 0:
            other += MOD

        ss = (s * s) % MOD
        other2 = sum_sq_sizes - ss
        if other2 < 0:
            other2 += MOD

        val = (other * other) % MOD
        val -= other2
        if val < 0:
            val += MOD

        tot += val
        if tot >= MOD:
            tot -= MOD

        add_scaled_poly(ans, pols[i], tot)
        i += 1

    return ans


def build_component(entry):
    global stamp
    stamp += 1
    if stamp == 1_000_000_000:
        seen[:] = [0] * n
        stamp = 1

    top = 0
    ord_sz = 0

    stack_node[top] = entry
    top += 1
    comp_par[entry] = -1
    seen[entry] = stamp

    while top:
        top -= 1
        u = stack_node[top]
        order[ord_sz] = u
        ord_sz += 1

        e = head[u]
        pu = comp_par[u]
        while e != -1:
            v = to[e]
            if tk[v] == 0 and v != pu and seen[v] != stamp:
                seen[v] = stamp
                comp_par[v] = u
                stack_node[top] = v
                top += 1
            e = nxt[e]

    i = ord_sz - 1
    while i >= 0:
        u = order[i]
        s = 1
        e = head[u]
        while e != -1:
            v = to[e]
            if seen[v] == stamp and comp_par[v] == u:
                s += szt[v]
            e = nxt[e]
        szt[u] = s
        i -= 1

    return ord_sz


def find_centroid(comp_size):
    i = 0
    while i < comp_size:
        u = order[i]
        max_part = comp_size - szt[u]

        e = head[u]
        while e != -1:
            v = to[e]
            if seen[v] == stamp and comp_par[v] == u and szt[v] > max_part:
                max_part = szt[v]
            e = nxt[e]

        if max_part * 2 <= comp_size:
            return u
        i += 1

    return order[0]


sys.setrecursionlimit(1_000_000)


def centroid_dfs(entry):
    comp_size = build_component(entry)
    c = find_centroid(comp_size)
    tk[c] = 1

    ans = process_root(c)

    e = head[c]
    while e != -1:
        v = to[e]
        if tk[v] == 0:
            cur = centroid_dfs(v)
            add_poly(ans, cur)
        e = nxt[e]

    return ans


precalc()
ans = centroid_dfs(0)

if len(ans) < n:
    ans.extend([0] * (n - len(ans)))

out = ' '.join(str(ans[i]) for i in range(1, n))
sys.stdout.write(out + '\n')
