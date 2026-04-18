#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MOD = 998244353, PRIMITIVE_ROOT = 3, MAX_LOG = 20 };

typedef struct {
    int *a;
    int sz;
    int cap;
} Poly;

static inline int add_mod(int x, int y) {
    x += y;
    if (x >= MOD) x -= MOD;
    return x;
}

static inline int sub_mod(int x, int y) {
    x -= y;
    if (x < 0) x += MOD;
    return x;
}

static inline int mul_mod(int x, int y) {
    return (int)((long long)x * y % MOD);
}

static int pow_mod(int a, int e) {
    int r = 1;
    while (e > 0) {
        if (e & 1) r = mul_mod(r, a);
        a = mul_mod(a, a);
        e >>= 1;
    }
    return r;
}

static inline void poly_init(Poly *p) {
    p->a = NULL;
    p->sz = 0;
    p->cap = 0;
}

static void poly_reserve(Poly *p, int need) {
    if (need <= p->cap) return;
    int ncap = p->cap ? p->cap : 1;
    while (ncap < need) ncap <<= 1;
    p->a = (int *)realloc(p->a, (size_t)ncap * sizeof(int));
    memset(p->a + p->cap, 0, (size_t)(ncap - p->cap) * sizeof(int));
    p->cap = ncap;
}

static void poly_ensure_size(Poly *p, int need_size) {
    if (need_size > p->cap) poly_reserve(p, need_size);
    if (need_size > p->sz) {
        memset(p->a + p->sz, 0, (size_t)(need_size - p->sz) * sizeof(int));
        p->sz = need_size;
    }
}

static inline void poly_free(Poly *p) {
    free(p->a);
    p->a = NULL;
    p->sz = 0;
    p->cap = 0;
}

static void add_poly(Poly *p, const Poly *q) {
    if (p->sz < q->sz) poly_ensure_size(p, q->sz);
    for (int i = 0; i < q->sz; ++i) {
        p->a[i] = add_mod(p->a[i], q->a[i]);
    }
}

static void sub_poly(Poly *p, const Poly *q) {
    if (p->sz < q->sz) poly_ensure_size(p, q->sz);
    for (int i = 0; i < q->sz; ++i) {
        p->a[i] = sub_mod(p->a[i], q->a[i]);
    }
}

static void scale_poly(Poly *p, int c) {
    for (int i = 0; i < p->sz; ++i) {
        p->a[i] = mul_mod(p->a[i], c);
    }
}

static int roots[MAX_LOG + 1], iroots[MAX_LOG + 1];

static void init_ntt_roots(void) {
    for (int level = 1; level <= MAX_LOG; ++level) {
        int len = 1 << level;
        roots[level] = pow_mod(PRIMITIVE_ROOT, (MOD - 1) / len);
        iroots[level] = pow_mod(roots[level], MOD - 2);
    }
}

static void ntt(int *a, int n, int invert) {
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
        if (i < j) {
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }
    }

    for (int len = 2, level = 1; len <= n; len <<= 1, ++level) {
        int wlen = invert ? iroots[level] : roots[level];
        int half = len >> 1;
        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < half; ++j) {
                int u = a[i + j];
                int v = mul_mod(a[i + j + half], w);
                a[i + j] = add_mod(u, v);
                a[i + j + half] = sub_mod(u, v);
                w = mul_mod(w, wlen);
            }
        }
    }

    if (invert) {
        int inv_n = pow_mod(n, MOD - 2);
        for (int i = 0; i < n; ++i) a[i] = mul_mod(a[i], inv_n);
    }
}

static Poly multiply(const Poly *a, const Poly *b) {
    Poly r;
    poly_init(&r);
    if (a->sz == 0 || b->sz == 0) return r;

    int need = a->sz + b->sz - 1;
    int n = 1;
    while (n < need) n <<= 1;

    int *fa = (int *)calloc((size_t)n, sizeof(int));
    int *fb = (int *)calloc((size_t)n, sizeof(int));
    memcpy(fa, a->a, (size_t)a->sz * sizeof(int));
    memcpy(fb, b->a, (size_t)b->sz * sizeof(int));

    ntt(fa, n, 0);
    ntt(fb, n, 0);
    for (int i = 0; i < n; ++i) fa[i] = mul_mod(fa[i], fb[i]);
    ntt(fa, n, 1);

    poly_ensure_size(&r, need);
    memcpy(r.a, fa, (size_t)need * sizeof(int));

    free(fa);
    free(fb);
    return r;
}

static unsigned char input_buf[1 << 20];
static size_t input_pos = 0, input_len = 0;

static int read_char_fast(void) {
    if (input_pos >= input_len) {
        input_len = fread(input_buf, 1, sizeof(input_buf), stdin);
        input_pos = 0;
        if (input_len == 0) return EOF;
    }
    return input_buf[input_pos++];
}

static int next_int(void) {
    int c = read_char_fast();
    while (c <= ' ') c = read_char_fast();
    int x = 0;
    while (c > ' ') {
        x = x * 10 + (c - '0');
        c = read_char_fast();
    }
    return x;
}

static int n;
static int *head, *to, *nxt;
static int edge_ptr;

static int *tk, *subt, *dep, *szt;
static int *par0, *comp_par, *seen;
static int *stack_node, *stack_par, *stack_depth, *order;
static int stamp = 1;

static void add_edge(int u, int v) {
    to[edge_ptr] = v;
    nxt[edge_ptr] = head[u];
    head[u] = edge_ptr++;
}

static void precalc(void) {
    int top = 0, ord = 0;
    stack_node[top++] = 0;
    par0[0] = -1;
    dep[0] = 0;

    while (top) {
        int u = stack_node[--top];
        order[ord++] = u;
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (v == par0[u]) continue;
            par0[v] = u;
            dep[v] = dep[u] + 1;
            stack_node[top++] = v;
        }
    }

    for (int i = ord - 1; i >= 0; --i) {
        int u = order[i];
        int s = 1;
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (par0[v] == u) s += subt[v];
        }
        subt[u] = s;
    }
}

static inline int get_directed_subtree_size(int x, int y) {
    if (dep[x] < dep[y]) return n - subt[y];
    return subt[x];
}

static void process_subtree(int start, int root, Poly *pol) {
    int top = 0;
    stack_node[top] = start;
    stack_par[top] = root;
    stack_depth[top] = 1;
    ++top;

    while (top) {
        --top;
        int u = stack_node[top];
        int p = stack_par[top];
        int d = stack_depth[top];

        int tot = 0;
        int acum = 1;

        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (v == p) continue;
            int dir_sz = get_directed_subtree_size(v, u);
            tot = add_mod(tot, mul_mod(dir_sz, acum));
            acum = add_mod(acum, dir_sz);
            if (!tk[v]) {
                stack_node[top] = v;
                stack_par[top] = u;
                stack_depth[top] = d + 1;
                ++top;
            }
        }

        tot = mul_mod(tot, 2);
        tot = add_mod(tot, 1);

        if (pol->sz < d + 1) poly_ensure_size(pol, d + 1);
        pol->a[d] = add_mod(pol->a[d], tot);
    }
}

static Poly process_root(int rt) {
    int k = 0;
    for (int e = head[rt]; e != -1; e = nxt[e]) ++k;

    Poly *pols = (Poly *)malloc((size_t)k * sizeof(Poly));
    int *sizes = (int *)malloc((size_t)k * sizeof(int));

    int idx = 0;
    for (int e = head[rt]; e != -1; e = nxt[e]) {
        int x = to[e];
        sizes[idx] = get_directed_subtree_size(x, rt);
        poly_init(&pols[idx]);
        if (!tk[x]) process_subtree(x, rt, &pols[idx]);
        ++idx;
    }

    Poly sum2, sum_sq;
    poly_init(&sum2);
    poly_init(&sum_sq);

    for (int i = 0; i < k; ++i) {
        Poly sq = multiply(&pols[i], &pols[i]);
        add_poly(&sum2, &pols[i]);
        add_poly(&sum_sq, &sq);
        poly_free(&sq);
    }

    Poly ans = multiply(&sum2, &sum2);
    sub_poly(&ans, &sum_sq);
    scale_poly(&ans, (MOD + 1) / 2);

    int sum_sizes = 0;
    int sum_sq_sizes = 0;
    for (int i = 0; i < k; ++i) {
        sum_sizes = add_mod(sum_sizes, sizes[i]);
        sum_sq_sizes = add_mod(sum_sq_sizes, mul_mod(sizes[i], sizes[i]));
    }

    for (int i = 0; i < k; ++i) {
        int tot = (int)(2LL * (n - sizes[i] - 1) % MOD);
        tot = add_mod(tot, 1);

        int other = sub_mod(sum_sizes, sizes[i]);
        int other2 = sub_mod(sum_sq_sizes, mul_mod(sizes[i], sizes[i]));
        tot = add_mod(tot, sub_mod(mul_mod(other, other), other2));

        scale_poly(&pols[i], tot);
        add_poly(&ans, &pols[i]);
    }

    for (int i = 0; i < k; ++i) poly_free(&pols[i]);
    poly_free(&sum2);
    poly_free(&sum_sq);
    free(pols);
    free(sizes);

    return ans;
}

static int build_component(int entry) {
    ++stamp;
    if (stamp == INT_MAX) {
        memset(seen, 0, (size_t)n * sizeof(int));
        stamp = 1;
    }

    int top = 0;
    int ord = 0;

    stack_node[top++] = entry;
    comp_par[entry] = -1;
    seen[entry] = stamp;

    while (top) {
        int u = stack_node[--top];
        order[ord++] = u;

        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (tk[v]) continue;
            if (v == comp_par[u]) continue;
            if (seen[v] == stamp) continue;
            seen[v] = stamp;
            comp_par[v] = u;
            stack_node[top++] = v;
        }
    }

    for (int i = ord - 1; i >= 0; --i) {
        int u = order[i];
        int s = 1;
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (seen[v] == stamp && comp_par[v] == u) s += szt[v];
        }
        szt[u] = s;
    }

    return ord;
}

static int find_centroid(int comp_size) {
    for (int i = 0; i < comp_size; ++i) {
        int u = order[i];
        int max_part = comp_size - szt[u];
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (seen[v] == stamp && comp_par[v] == u && szt[v] > max_part) {
                max_part = szt[v];
            }
        }
        if (max_part * 2 <= comp_size) return u;
    }
    return order[0];
}

static Poly centroid_dfs(int entry) {
    int comp_size = build_component(entry);
    int c = find_centroid(comp_size);
    tk[c] = 1;

    Poly ans = process_root(c);

    for (int e = head[c]; e != -1; e = nxt[e]) {
        int v = to[e];
        if (tk[v]) continue;
        Poly cur = centroid_dfs(v);
        add_poly(&ans, &cur);
        poly_free(&cur);
    }

    return ans;
}

static Poly solve_all(void) {
    memset(tk, 0, (size_t)n * sizeof(int));
    precalc();
    return centroid_dfs(0);
}

int main(void) {
    n = next_int();
    int m = n - 1;

    head = (int *)malloc((size_t)n * sizeof(int));
    to = (int *)malloc((size_t)(2 * m) * sizeof(int));
    nxt = (int *)malloc((size_t)(2 * m) * sizeof(int));
    edge_ptr = 0;

    for (int i = 0; i < n; ++i) head[i] = -1;

    for (int i = 0; i < m; ++i) {
        int u = next_int() - 1;
        int v = next_int() - 1;
        add_edge(u, v);
        add_edge(v, u);
    }

    tk = (int *)calloc((size_t)n, sizeof(int));
    subt = (int *)calloc((size_t)n, sizeof(int));
    dep = (int *)calloc((size_t)n, sizeof(int));
    szt = (int *)calloc((size_t)n, sizeof(int));
    par0 = (int *)malloc((size_t)n * sizeof(int));
    comp_par = (int *)malloc((size_t)n * sizeof(int));
    seen = (int *)calloc((size_t)n, sizeof(int));

    stack_node = (int *)malloc((size_t)n * sizeof(int));
    stack_par = (int *)malloc((size_t)n * sizeof(int));
    stack_depth = (int *)malloc((size_t)n * sizeof(int));
    order = (int *)malloc((size_t)n * sizeof(int));

    init_ntt_roots();
    Poly ans = solve_all();

    if (ans.sz < n) poly_ensure_size(&ans, n);
    for (int i = 1; i < n; ++i) {
        printf("%d%c", ans.a[i], (i + 1 == n) ? '\n' : ' ');
    }

    poly_free(&ans);
    free(head);
    free(to);
    free(nxt);
    free(tk);
    free(subt);
    free(dep);
    free(szt);
    free(par0);
    free(comp_par);
    free(seen);
    free(stack_node);
    free(stack_par);
    free(stack_depth);
    free(order);
    return 0;
}
