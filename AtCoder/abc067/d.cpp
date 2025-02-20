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

void solve(){
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<int> par(n);
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        par[u] = p;
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
    };
    dfs(dfs, 0, 0);
    vector<int> path;
    int cur = n-1;
    while (cur) {
        path.pb(cur), cur = par[cur];
    }
    path.pb(0);
    int l = 1, r = sz(path)-2, turn = 0;
    vector<int> color(n, -1);
    color[0] = 0; color[n-1] = 1;
    while (l <= r) {
        if (turn % 2) color[path[l++]] = 1;
        else color[path[r--]] = 0;
        turn ^= 1;
    }
    //for (auto x : color) cout << x << ' ';
    //cout << endl;
    //exit(0);
    vector<int> x1, x2;
    for (int i = 0; i < n; ++i) {
        if (color[i] == 0) {
            for (auto v : g[i]) if (color[v] == -1) x1.pb(v);
        }
        if (color[i] == 1) {
            for (auto v : g[i]) if (color[v] == -1) x2.pb(v);
        }
    }
    while (true) {
        bool ok = 0;
        if (turn % 2) {
            while (!x2.empty()) {
                int u = x2.back();
                x2.pop_back();
                if (color[u] != -1) continue;
                color[u] = 1;
                for (auto v : g[u]) if (color[v] == -1) x2.pb(v);
                ok = 1;
                break;
            }
        } else {
            while (!x1.empty()) {
                int u = x1.back();
                x1.pop_back();
                if (color[u] != -1) continue;
                color[u] = 0;
                for (auto v : g[u]) if (color[v] == -1) x1.pb(v);
                ok = 1;
                break;
            }
        }
        if (!ok) {
            if (turn) cout << "Fennec" << endl;
            else cout << "Snuke" << endl;
            exit(0);
        }
        turn ^= 1;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
