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
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
struct Cmp {
    bool operator ()(const array<int, 4>& a, const array<int, 4>& b) const {
        int lhs = a[0] * b[1], rhs = a[1] * b[0];
        if (lhs != rhs) return lhs < rhs;
        return pair(a[2], a[3]) < pair(b[2], b[3]);
    }
};

int solve(int n, vector<int> pp, vector<int> v) {
    vector<vector<int>> g(n), g2(n);
    vector<int> par(n, -1), tam(n);
    for (int i = 1; i < n; ++i) g[pp[i]].pb(i);
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        par[u] = (v[u] ? u : par[p]);
        if (v[u] == 0 and par[u] != -1) tam[par[u]]++;
        if (v[u] == 1 and par[p] != -1 and u != p) g2[par[p]].pb(u);
        for (auto w : g[u]) self(self, w, u);
    };
    dfs(dfs, 0, 0);
    int m = accumulate(all(v), 0);
    using T = multiset<array<int, 4>, Cmp>;
    vector<T> perm(n);
    auto merge = [&] (T &s1, T &s2) { assert(sz(s1) >= sz(s2)); for (auto x : s2) s1.insert(x); };
    auto calc = [&] (auto&& self, int u) -> void {
        for (auto w : g2[u]) {
            self(self, w);
            if (sz(perm[w]) > sz(perm[u])) swap(perm[u], perm[w]);
            merge(perm[u], perm[w]);
        }
        int s1 = tam[u], qt1 = 1, tot = m * tam[u];
        while (!perm[u].empty()) {
            auto [s2, qt2, tot2, fds] = *rbegin(perm[u]);
            if (s2 * qt1 < s1 * qt2) break;
            perm[u].erase({s2, qt2, tot2, fds});
            tot = tot2 + tot - s1 * qt2;
            s1 += s2;
            qt1 += qt2;
        }
        perm[u].insert({s1, qt1, tot, rnd(0, 1e18)});
    };
    T S;
    for (int i = 0; i < n; ++i) {
        if (v[i] == 1 and (i == 0 or par[pp[i]] == -1)) {
            calc(calc, i);
            if (sz(S) < sz(perm[i])) swap(S, perm[i]);
            merge(S, perm[i]);
        }
    }
    int ans = 0, foi = 0;
    for (auto [s, q, t, fds] : S) {
        t -= s * foi;
        ans += t;
        foi += q;
    }
    return ans;
}

int brute(int n, vector<int> pp, vector<int> a) {
    vector<int> dp(1<<n, 1e18);
    int qt0 = n - accumulate(all(a), 0);
    dp[1] = a[0] * qt0;
    for (int i = 2; i < (1 << n); ++i) {
        int tem = 0;
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) {}
            else tem += (a[j] == 0);
        }
        for (int j = 1; j < n; ++j) {
            if ((i >> j & 1) and (i >> pp[j] & 1)) {
                ckmin(dp[i], dp[i-(1<<j)] + tem * a[j]);
            }
        }
    }
    return dp.back();
}


int32_t main() {_
#ifndef gato
    int n; cin >> n;
    vector<int> pp(n);
    for (int i = 1; i < n; ++i) cin >> pp[i], --pp[i];
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    cout << solve(n, pp, a) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 12);
        vector<int> pp(n);
        for (int i = 1; i < n; ++i) pp[i] = rnd(0, i-1);
        vector<int> a(n);
        for (auto& x : a) x = rnd(0, 1);
        int my = solve(n, pp, a), ans = brute(n, pp, a);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (int i = 1; i < n; ++i) cout << pp[i]+1 << " ";
            cout << endl;
            for (auto x : a) cout << x << " ";
            cout << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
