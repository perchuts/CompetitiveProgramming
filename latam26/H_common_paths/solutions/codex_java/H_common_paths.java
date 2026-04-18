import java.io.InputStream;
import java.util.Arrays;

public class codex {
    static final int MOD = 998244353;
    static final int ROOT = 3;
    static final int MAX_LOG = 20;
    static final int INV2 = (MOD + 1) / 2;

    static int n;
    static int[] head, to, next;
    static int edgePtr;

    static int[] tk, subt, dep, szt;
    static int[] par0, compPar, seen;
    static int[] stackNode, stackPar, stackDepth, order;
    static int stamp = 1;

    static int[] roots = new int[MAX_LOG + 1];
    static int[] invRoots = new int[MAX_LOG + 1];

    static final class FastScanner {
        private final InputStream in = System.in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0;
        private int len = 0;

        private int read() {
            if (ptr >= len) {
                try {
                    len = in.read(buffer);
                    ptr = 0;
                } catch (Exception e) {
                    return -1;
                }
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }

        int nextInt() {
            int c = read();
            while (c <= ' ') c = read();
            int x = 0;
            while (c > ' ') {
                x = x * 10 + (c - '0');
                c = read();
            }
            return x;
        }
    }

    static final class Poly {
        int[] a = new int[0];
        int size = 0;

        void ensureSize(int need) {
            if (need > a.length) {
                int cap = Math.max(1, a.length);
                while (cap < need) cap <<= 1;
                a = Arrays.copyOf(a, cap);
            }
            if (need > size) {
                Arrays.fill(a, size, need, 0);
                size = need;
            }
        }
    }

    static int addMod(int x, int y) {
        x += y;
        if (x >= MOD) x -= MOD;
        return x;
    }

    static int subMod(int x, int y) {
        x -= y;
        if (x < 0) x += MOD;
        return x;
    }

    static int mulMod(int x, int y) {
        return (int) ((long) x * y % MOD);
    }

    static int powMod(int a, int e) {
        int r = 1;
        while (e > 0) {
            if ((e & 1) != 0) r = mulMod(r, a);
            a = mulMod(a, a);
            e >>= 1;
        }
        return r;
    }

    static void initRoots() {
        for (int level = 1; level <= MAX_LOG; level++) {
            int len = 1 << level;
            roots[level] = powMod(ROOT, (MOD - 1) / len);
            invRoots[level] = powMod(roots[level], MOD - 2);
        }
    }

    static void ntt(int[] a, boolean invert) {
        int n = a.length;
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            while ((j & bit) != 0) {
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

        for (int len = 2, level = 1; len <= n; len <<= 1, level++) {
            int wlen = invert ? invRoots[level] : roots[level];
            int half = len >> 1;
            for (int i = 0; i < n; i += len) {
                int w = 1;
                int limit = i + half;
                for (int j = i, k = i + half; j < limit; j++, k++) {
                    int u = a[j];
                    int v = mulMod(a[k], w);
                    a[j] = addMod(u, v);
                    a[k] = subMod(u, v);
                    w = mulMod(w, wlen);
                }
            }
        }

        if (invert) {
            int invN = powMod(n, MOD - 2);
            for (int i = 0; i < n; i++) a[i] = mulMod(a[i], invN);
        }
    }

    static Poly multiply(Poly A, Poly B) {
        Poly res = new Poly();
        if (A.size == 0 || B.size == 0) return res;

        int need = A.size + B.size - 1;
        int n = 1;
        while (n < need) n <<= 1;

        int[] fa = new int[n];
        int[] fb = new int[n];
        System.arraycopy(A.a, 0, fa, 0, A.size);
        System.arraycopy(B.a, 0, fb, 0, B.size);

        ntt(fa, false);
        ntt(fb, false);
        for (int i = 0; i < n; i++) fa[i] = mulMod(fa[i], fb[i]);
        ntt(fa, true);

        res.ensureSize(need);
        System.arraycopy(fa, 0, res.a, 0, need);
        return res;
    }

    static void addPoly(Poly p, Poly q) {
        if (p.size < q.size) p.ensureSize(q.size);
        for (int i = 0; i < q.size; i++) p.a[i] = addMod(p.a[i], q.a[i]);
    }

    static void subPoly(Poly p, Poly q) {
        if (p.size < q.size) p.ensureSize(q.size);
        for (int i = 0; i < q.size; i++) p.a[i] = subMod(p.a[i], q.a[i]);
    }

    static void scalePoly(Poly p, int c) {
        for (int i = 0; i < p.size; i++) p.a[i] = mulMod(p.a[i], c);
    }

    static void addEdge(int u, int v) {
        to[edgePtr] = v;
        next[edgePtr] = head[u];
        head[u] = edgePtr++;
    }

    static int getDirectedSubtreeSize(int x, int y) {
        if (dep[x] < dep[y]) return n - subt[y];
        return subt[x];
    }

    static void precalc() {
        int top = 0;
        int ord = 0;

        stackNode[top++] = 0;
        par0[0] = -1;
        dep[0] = 0;

        while (top > 0) {
            int u = stackNode[--top];
            order[ord++] = u;
            for (int e = head[u]; e != -1; e = next[e]) {
                int v = to[e];
                if (v == par0[u]) continue;
                par0[v] = u;
                dep[v] = dep[u] + 1;
                stackNode[top++] = v;
            }
        }

        for (int i = ord - 1; i >= 0; i--) {
            int u = order[i];
            int s = 1;
            for (int e = head[u]; e != -1; e = next[e]) {
                int v = to[e];
                if (par0[v] == u) s += subt[v];
            }
            subt[u] = s;
        }
    }

    static void processSubtree(int start, int root, Poly pol) {
        int top = 0;
        stackNode[top] = start;
        stackPar[top] = root;
        stackDepth[top] = 1;
        top++;

        while (top > 0) {
            top--;
            int u = stackNode[top];
            int p = stackPar[top];
            int d = stackDepth[top];

            int tot = 0;
            int acum = 1;

            for (int e = head[u]; e != -1; e = next[e]) {
                int v = to[e];
                if (v == p) continue;
                int dir = getDirectedSubtreeSize(v, u);
                tot = addMod(tot, mulMod(dir, acum));
                acum = addMod(acum, dir);
                if (tk[v] == 0) {
                    stackNode[top] = v;
                    stackPar[top] = u;
                    stackDepth[top] = d + 1;
                    top++;
                }
            }

            tot = mulMod(tot, 2);
            tot = addMod(tot, 1);

            if (pol.size < d + 1) pol.ensureSize(d + 1);
            pol.a[d] = addMod(pol.a[d], tot);
        }
    }

    static Poly processRoot(int rt) {
        int k = 0;
        for (int e = head[rt]; e != -1; e = next[e]) k++;

        Poly[] pols = new Poly[k];
        int[] sizes = new int[k];

        int idx = 0;
        for (int e = head[rt]; e != -1; e = next[e]) {
            int x = to[e];
            sizes[idx] = getDirectedSubtreeSize(x, rt);
            pols[idx] = new Poly();
            if (tk[x] == 0) processSubtree(x, rt, pols[idx]);
            idx++;
        }

        Poly sum2 = new Poly();
        Poly sumSq = new Poly();

        for (int i = 0; i < k; i++) {
            Poly sq = multiply(pols[i], pols[i]);
            addPoly(sum2, pols[i]);
            addPoly(sumSq, sq);
        }

        Poly ans = multiply(sum2, sum2);
        subPoly(ans, sumSq);
        scalePoly(ans, INV2);

        int sumSizes = 0;
        int sumSqSizes = 0;
        for (int i = 0; i < k; i++) {
            sumSizes = addMod(sumSizes, sizes[i]);
            sumSqSizes = addMod(sumSqSizes, mulMod(sizes[i], sizes[i]));
        }

        for (int i = 0; i < k; i++) {
            int tot = (int) (2L * (n - sizes[i] - 1) % MOD);
            tot = addMod(tot, 1);
            int other = subMod(sumSizes, sizes[i]);
            int other2 = subMod(sumSqSizes, mulMod(sizes[i], sizes[i]));
            tot = addMod(tot, subMod(mulMod(other, other), other2));

            scalePoly(pols[i], tot);
            addPoly(ans, pols[i]);
        }

        return ans;
    }

    static int buildComponent(int entry) {
        stamp++;
        if (stamp == Integer.MAX_VALUE) {
            Arrays.fill(seen, 0);
            stamp = 1;
        }

        int top = 0;
        int ord = 0;

        stackNode[top++] = entry;
        compPar[entry] = -1;
        seen[entry] = stamp;

        while (top > 0) {
            int u = stackNode[--top];
            order[ord++] = u;

            for (int e = head[u]; e != -1; e = next[e]) {
                int v = to[e];
                if (tk[v] != 0) continue;
                if (v == compPar[u]) continue;
                if (seen[v] == stamp) continue;
                seen[v] = stamp;
                compPar[v] = u;
                stackNode[top++] = v;
            }
        }

        for (int i = ord - 1; i >= 0; i--) {
            int u = order[i];
            int s = 1;
            for (int e = head[u]; e != -1; e = next[e]) {
                int v = to[e];
                if (seen[v] == stamp && compPar[v] == u) s += szt[v];
            }
            szt[u] = s;
        }

        return ord;
    }

    static int findCentroid(int compSize) {
        for (int i = 0; i < compSize; i++) {
            int u = order[i];
            int maxPart = compSize - szt[u];
            for (int e = head[u]; e != -1; e = next[e]) {
                int v = to[e];
                if (seen[v] == stamp && compPar[v] == u && szt[v] > maxPart) {
                    maxPart = szt[v];
                }
            }
            if (maxPart * 2 <= compSize) return u;
        }
        return order[0];
    }

    static Poly centroidDfs(int entry) {
        int compSize = buildComponent(entry);
        int c = findCentroid(compSize);
        tk[c] = 1;

        Poly ans = processRoot(c);

        for (int e = head[c]; e != -1; e = next[e]) {
            int v = to[e];
            if (tk[v] != 0) continue;
            Poly cur = centroidDfs(v);
            addPoly(ans, cur);
        }

        return ans;
    }

    public static void main(String[] args) {
        FastScanner fs = new FastScanner();
        n = fs.nextInt();
        int m = n - 1;

        head = new int[n];
        Arrays.fill(head, -1);
        to = new int[2 * m];
        next = new int[2 * m];
        edgePtr = 0;

        for (int i = 0; i < m; i++) {
            int u = fs.nextInt() - 1;
            int v = fs.nextInt() - 1;
            addEdge(u, v);
            addEdge(v, u);
        }

        tk = new int[n];
        subt = new int[n];
        dep = new int[n];
        szt = new int[n];
        par0 = new int[n];
        compPar = new int[n];
        seen = new int[n];

        stackNode = new int[n];
        stackPar = new int[n];
        stackDepth = new int[n];
        order = new int[n];

        initRoots();
        precalc();

        Poly ans = centroidDfs(0);
        if (ans.size < n) ans.ensureSize(n);

        StringBuilder out = new StringBuilder();
        for (int i = 1; i < n; i++) {
            if (i > 1) out.append(' ');
            out.append(ans.a[i]);
        }
        out.append('\n');
        System.out.print(out);
    }
}
