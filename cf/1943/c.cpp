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
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<int> dist(n), par(n);
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        for (auto v : g[u]) {
            if (v == p) continue;
            dist[v] = 1 + dist[u];
            par[v] = u;
            self(self, v, u);
        }
    };
    dfs(dfs, 0, 0);
    int src = 0;
    for (int i = 0; i < n; ++i) if (dist[src] < dist[i]) src = i;
    dist[src] = 0;
    dfs(dfs, src, src);
    int other = 0;
    for (int i = 0; i < n; ++i) if (dist[other] < dist[i]) other = i;
    vector<int> diam = {other};
    while (other != src) other = par[other], diam.pb(other);
    int d = sz(diam);
    if (d & 3) {
        cout << d/2+1 << endl;
        for (int i = 0; i <= d/2; ++i) cout << diam[d/2]+1 << " " << i << endl;
        return;
    }
    cout << d/2 << endl;
    for (int i = 1; i < d/2; i += 2) {
        cout << diam[d/2]+1 << " " << i << endl;
        cout << diam[d/2-1]+1 << " " << i << endl;
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
