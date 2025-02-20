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
    vector<vector<ii>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v, c; cin >> u >> v >> c;
        --u, --v;
        g[u].pb({v, c});
        g[v].pb({u, c});
    }
    int q, k; cin >> q >> k;
    --k;
    vector<int> h(n);
    auto dfs = [&] (auto&& self, int u, int p, int e = 0) -> void {
        h[u] = h[p] + e;
        for (auto [v, c] : g[u]) {
            if (v == p) continue;
            self(self, v, u, c);
        }
    };
    dfs(dfs, k, k);
    while (q--) {
        int u, v; cin >> u >> v;
        --u, --v;
        cout << h[u] + h[v] << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
