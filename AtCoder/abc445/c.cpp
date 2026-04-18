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
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x, --x;
    vector<vector<int>> g(n);
    vector<vector<int>> cycle;
    vector<int> vis(n), start(n), h(n), isc(n), id(n);
    for (int i = 0; i < n; ++i) g[a[i]].pb(i);
    auto dfs = [&] (auto&& self, int u, int hx) -> void {
        id[u] = sz(cycle)-1;
        h[u] = hx;
        vis[u] = 3;
        for (auto v : g[u]) {
            if (vis[v] == 3) continue;
            if (isc[v] == 0) start[v] = start[u];
            self(self, v, hx + (isc[v] == 0));
        }
    };
    for (int i = 0; i < n; ++i) {
        if (vis[i]) continue;
        int cur = i;
        while (!vis[cur]) vis[cur] = 1, cur = a[cur];
        cycle.pb({});
        while (vis[cur] == 1) start[cur] = sz(cycle.back()), cycle.back().pb(cur), vis[cur] = 2, isc[cur] = 1, cur = a[cur];
        dfs(dfs, cur, cur);
    }
    auto fexp = [&] (int b, int e, int m) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % m;
            e /= 2, b = b * b % m;
        }
        return ans;
    };
    for (int i = 0; i < n; ++i) {
        int z = (fexp(10, 100, sz(cycle[id[i]])) + start[i] - h[i] + n * sz(cycle[id[i]])) % sz(cycle[id[i]]);
        cout << cycle[id[i]][z] + 1 << " "; 
    }
    cout << endl;
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
