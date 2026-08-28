#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ull

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

void solve() {
    int n, q; cin >> n >> q;
    vector<vector<int>> g(n);
    vector<int> lvl(n+1);
    vector<vector<int>> bl(n+1, vector<int>(18));
    const int K = -1;
    vector<int> c(n), hsh(n), sp(n+1);
    for (auto& x : c) {
        char col; cin >> col;
        x = (col == '1');
    }
    bl[n] = vector<int>(18, n);
    int H = 0;
    for (int i = 0; i < n; ++i) {
        hsh[i] = rnd(0, K);
        if (c[i]) H ^= hsh[i];
    }
    vector<int> ini(n), fim(n);
    int T = 0;
    auto pre = [&] (auto&& self, int u, int p) -> void {
        bl[u][0] = p;
        lvl[u] = 1 + lvl[p];
        sp[u] = sp[p] ^ hsh[u];
        for (int i = 1; i < 18; ++i) bl[u][i] = bl[bl[u][i-1]][i-1];
        ini[u] = ++T;
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
        fim[u] = ++T;
    };
    auto lca = [&] (int u, int v) {
        if (lvl[u] < lvl[v]) swap(u, v);
        for (int i = 17; ~i; --i) {
            if (lvl[bl[u][i]] >= lvl[v]) u = bl[u][i];
        }
        if (u == v) return u;
        for (int i = 17; ~i; --i) {
            if (bl[u][i] != bl[v][i]) u = bl[u][i], v = bl[v][i];
        }
        return bl[u][0];
    };
    auto sum_path = [&] (int u, int v) {
        int l = lca(u, v);
        return sp[u] ^ sp[v] ^ hsh[l];
    };
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    pre(pre, 0, n);
    set<ii> inis, fins;
    for (int i = 0; i < n; ++i) {
        if (c[i]) {
            inis.insert({ini[i], i});
            fins.insert({fim[i], i});
        }
    }
    while (q--) {
        int u; cin >> u; --u;
        H ^= hsh[u];
        int i = u;
        if (c[u]) {
            inis.erase({ini[i], i});
            fins.erase({fim[i], i});
        } else {
            inis.insert({ini[i], i});
            fins.insert({fim[i], i});
        }
        if (inis.empty()) {
            cout << "No" << endl;
        } else if (sz(inis) == 1) {
            cout << "Yes" << endl;
        } else {
            int u = begin(fins)->second;
            int v = prev(end(inis))->second;
            if (u == v) v = prev(end(fins))->second;
            cout << (H == sum_path(u, v) ? "Yes" : "No") << endl;
        }
        c[u] ^= 1;
    }
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
