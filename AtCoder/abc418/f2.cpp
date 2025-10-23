#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve() {

    int n, q; cin >> n >> q;

    vector<int> fat(n+1, 1), ifat(n+1), fib(n+1); 

    // init
    {
        fib[1] = 1;
        for (int i = 2; i <= n; ++i) fib[i] = (fib[i-1] + fib[i-2]) % mod;
        for (int i = 1; i <= n; ++i) fat[i] = i * fat[i-1] % mod;
        auto fexp = [&] (int b, int e) {
            int ans = 1;
            while (e) {
                if (e&1) ans = ans * b % mod;
                e /= 2, b = b * b % mod;
            }
            return ans;
        };
        ifat.back() = fexp(fat.back(), mod-2);
        for (int i = n-1; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    }

    auto ncr = [&] (int a, int b) { if (a < b or b < 0) return 0LL; return fat[a] * ifat[b] % mod * ifat[a-b] % mod; };

    struct node {
        vector<vector<int>> f;
        int freeL = 0, freeR = 0, tot = 0;
        int defL = -1, defR = -1;
        node() {
            f = vector<vector<int>>(2, vector<int>(2, 0));
        }
    };

    auto print_state = [&] (node a) {
        cout << "freeL: " << a.freeL << " freeR: " << a.freeR << " defL: " << a.defL << " defR: " << a.defR << endl;
        cout << "f: " << endl;
        for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) cout << a.f[i][j] << " \n"[j==1];
        cout << endl;
    };
    auto merge = [&] (const node& a, const node& b) {
        node c;
        c.freeL = a.freeL + (a.tot == a.freeL ? b.freeL : 0);
        c.defL = (a.tot == a.freeL ? b.defL : a.defL);
        c.defR = (b.tot == b.freeL ? a.defR : b.defR);
        c.freeR = b.freeR + (b.tot == b.freeR ? a.freeR : 0);
        c.tot = a.tot + b.tot;
        assert(c.tot >= 2);
        if (c.tot == c.freeL) return c;
        if (a.tot == a.freeL) {
            c.f = b.f;
            return c;
        }
        if (b.tot == b.freeL) {
            c.f = a.f;
            return c;
        }
        // f[a][b] = a eh o valor do PRIMEIRO cara depois do primeiro A[i] != -1, b eh o valor do ultimo cara diferente de -1
        int N = a.freeR + b.freeL + 1;
        int K = b.defL - a.defL;
        for (int e1 = 0; e1 < 2; ++e1) {
            for (int e2 = 0; e2 < 2; ++ e2) {
                for (int d1 = 0; d1 < 2; ++d1) {
                    for (int d2 = 0; d2 < 2; ++d2) {
                        int block = min(N, d1+e2);
                        int ways = a.f[e1][d1] * ncr(N - K + 1 - block, K) % mod * b.f[e2][d2] % mod;
                        c.f[e1][d2] += ways;
                        if (c.f[e1][d2] >= mod) c.f[e1][d2] -= mod;
                    }
                }
            }
        }
        return c;
    };

    vector<node> seg(4*n);

    auto upd = [&] (auto&& self, int i, int l, int r, int x, int k) -> void {
        if (l == r) {
            seg[i].defL = seg[i].defR = k;
            if (k == -1) {
                seg[i].freeL = seg[i].freeR = 1;
            } else {
                seg[i].freeL = seg[i].freeR = 0;
                seg[i].f[0][0] = seg[i].f[1][1] = 1;
            }
            return;
        }
        int md = (l + r) / 2;
        if (x <= md) self(self, 2*i, l, md, x, k);
        else self(self, 2*i+1, md+1, r, x, k);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };

    auto build = [&] (auto&& self, int i, int l, int r) -> void {
        if (l == r) {
            seg[i].freeL = seg[i].freeR = seg[i].tot = 1;
            return;
        }
        int md = (l + r) / 2;
        self(self, 2*i, l, md);
        self(self, 2*i+1, md+1, r);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };

    build(build, 1, 0, n-1);
    //flag = true;

    while (q--) {
        int x, y; cin >> x >> y; --x;
        upd(upd, 1, 0, n-1, x, y);
        int ans = 0;
        cout << "seg 1: " << endl;
        print_state(seg[1]);
        cout << "seg 2: " << endl;
        print_state(seg[2]);
        cout << "seg 3: " << endl;
        print_state(seg[3]);
        if (seg[1].freeL == n) {
            cout << fib[n] << endl;
        } else if (seg[1].freeL + seg[1].freeR == n-1) { 
            int N = seg[1].freeL + 1;
            int K = seg[1].defL;
            for (int i = 0; i < 2; ++i) {
                int nn = N - 1;
                int kk = K - i;
                int sobra = seg[1].freeR - i;
                int ways = ncr(nn + kk - 1, kk);
                if (sobra > 0) ways = ways * fib[sobra] % mod;
                ans = (ans + ways) % mod;
            }
        } else {
            for (int i = 0; i < 4; ++i) {
                int esq = i>>1&1, dir = i&1;
                int ways = seg[1].f[esq][dir];
                int fl = seg[1].freeL + 1 - esq, fr = seg[1].freeR - dir;
                ways = ways * ncr(fl-seg[1].defL+1, seg[1].defL);
                if (fr > 0) ways = ways * fib[fr] % mod;
                ans = (ans + ways) % mod;
            }
        }
        cout << ans << endl;
    }
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
