#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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

int solve(int n, vector<int> p) {
    vector<int> pw(n+1, 1);
    int ans = (n-1)*(n-1) % mod;
    for (int i = 1; i <= n; ++i) pw[i] = 2 * pw[i-1] % mod;
    ans = ans * (pw[n]-1) % mod;
    for (int i = 1; i <= n; ++i) {
        int ways = pw[n-i] * (i-1) % mod * (n-1) % mod;
        ans = (ans + 4*(mod-ways)) % mod;
    }
    auto rotate90 = [&] () {
        vector<int> np(n);
        for (int i = 0; i < n; ++i) np[p[i]] = n-1-i;
        swap(p, np);
    };
    struct node { int atv, ss; };
    vector<node> seg(4*n);
    vector<int> lz(4*n);
    auto push = [&] (int i, int l, int r) {
        seg[i].ss = seg[i].ss * pw[lz[i]] % mod;
        if (l != r) lz[2*i] += lz[i], lz[2*i+1] += lz[i];
        lz[i] = 0;
    };
    auto merge = [&] (node a, node b) {
        node c;
        c.atv = a.atv + b.atv;
        c.ss = a.ss + b.ss;
        if (c.ss >= mod) c.ss -= mod;
        return c;
    };
    auto upd_point = [&] (auto&& self, int i, int l, int r, int x, int val) -> void {
        push(i, l, r);
		if (x < l or r < x) return;
        if (l == r) {
            seg[i].atv = 1;
            seg[i].ss = val;
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md, x, val);
        self(self, 2*i+1, md+1, r, x, val);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };
    auto upd_range = [&] (auto&& self, int i, int l, int r, int x, int y) -> void {
        push(i, l, r);
        if (r < x or y < l) return;
        if (x <= l and r <= y) {
            lz[i]++;
            push(i, l, r);
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md, x, y);
        self(self, 2*i+1, md+1, r, x, y);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };
    node nulo;
    nulo.ss = nulo.atv = 0;
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> node {
        push(i, l, r);
        if (r < x or y < l) return nulo;
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        return merge(self(self, 2*i, l, md, x, y), self(self, 2*i+1, md+1, r, x, y));
    };
    for (int w = 0; w < 4; ++w) {
        // intersection happening at the bottom
        // i <= j
        // p[i] >= p[j]
        // i * p[j] * 2^{# k : i < k, p[k] > p[j]}
        // i * p[j] * 2^{# k : j < k, p[k] > p[j]} * 2^{# k : i < k < j, p[k] > p[j]}
        // i * 2^{# k : i < k < j, p[k] > p[j]} * (p[j] * 2^{# k : j < k, p[k] > p[j]})
        for (int i = 0; i < 4 * n; ++i) seg[i].ss = seg[i].atv = lz[i] = 0;
        for (int i = n-1; ~i; --i) {
            node resp = query(query, 1, 0, n-1, 0, p[i]);
            ans = (ans + i * resp.ss) % mod;
            int cf = p[i] * pw[(n-1-i-resp.atv)] % mod;
            upd_range(upd_range, 1, 0, n-1, 0, p[i]);
            upd_point(upd_point, 1, 0, n-1, p[i], cf);
            ans = (ans + i * cf) % mod;
        }
        rotate90();
    }
    return ans;
}

int brute(int n, vector<int> p) {
    vector<int> pw(n+1, 1);
    int ans = (n-1)*(n-1) % mod;
    for (int i = 1; i <= n; ++i) pw[i] = 2 * pw[i-1] % mod;
    ans = ans * (pw[n]-1) % mod;
    for (int i = 1; i <= n; ++i) {
        int ways = pw[n-i] * (i-1) % mod * (n-1) % mod;
        ans = (ans + 4*(mod-ways)) % mod;
    }
    auto rotate90 = [&] () {
        vector<int> np(n);
        for (int i = 0; i < n; ++i) np[p[i]] = n-1-i;
        swap(p, np);
    };
    for (int w = 0; w < 4; ++w) {
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                // i has to be the leftmost, j has to be the bottommost
                if (p[i] < p[j]) continue;
                int cnt = 0;
                for (int k = i+1; k < n; ++k) cnt += (p[k] > p[j]);
                int ways = pw[cnt] * i % mod * p[j] % mod; 
                ans = (ans + ways) % mod;
            }
        }
        rotate90();
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int n; cin >> n;
    vector<int> p(n);
    for (auto& x : p) cin >> x, --x;
    cout << solve(n, p) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 100);
        vector<int> p(n); iota(all(p), 0); shuffle(all(p), rng);
        int my = solve(n, p), ans = brute(n, p);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : p) cout << x + 1 << " ";
            cout << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
