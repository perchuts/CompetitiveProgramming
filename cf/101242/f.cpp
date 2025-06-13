#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
	using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;

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
    int n, m; cin >> n >> m;
    // n = # folhas, m = # nos internos - 1
    vector<string> useless(n);
    int N = n+m+1;
    vector<vector<ii>> g(N);
    for (int i = 0; i < n; ++i) {
        cin >> useless[i];
        int p, w; cin >> p >> w; 
        g[p].pb({m+1+i, w});
    }
    for (int i = 1; i <= m; ++i) {
        int p, w; cin >> p >> w;
        g[p].pb({i, w});
    }
    vector<int> up(N), dir(N, -1);
    auto pre = [&] (auto&& self, int u, int w) -> void {
        if (g[u].empty()) {
            up[u] = w;
            return;
        }
        for (auto [v, __] : g[u]) self(self, v, __);
        up[u] = 1e18;
        for (auto [v, __] : g[u]) {
            if (ckmin(up[u], up[v] + w)) dir[u] = v;
        }
    };
    pre(pre, 0, 0);
    ord_set<ii> sexo;
    vector<int> ini(n), win(N);
    auto pre2 = [&] (auto&& self, int u, int w) -> void { 
        if (dir[u] == -1) {
            cout << "+ " << w << ' ' << useless[u-m-1] << endl;
            sexo.insert({w, u-m-1});
            ini[u-m-1] = w;
            win[u] = u-m-1;
            return;
        }
        for (auto [v, __] : g[u]) {
            if (v == dir[u]) self(self, v, w+__);
            else self(self, v, __);
        }
        win[u] = win[dir[u]];
    };
    pre2(pre2, 0, 0); 
    vector<int> ans(n);
    auto solve = [&] (auto&& self, int u, int w) -> void {
        if (dir[u] == -1) {
            cout << useless[u-m-1] << endl;
            for (auto [x, y] : sexo) cout << x << ' ' << y << endl;
            ans[u-m-1] = n+1-sexo.order_of_key({w, inf});
            return;
        }
        sexo.erase({up[u], win[u]});
        sexo.insert({up[dir[u]], win[u]});
        for (auto [v, w2] : g[u]) self(self, v, w+w2);
        sexo.erase({up[dir[u]], win[u]});
        sexo.insert({up[u], win[u]});
    };
    solve(solve, 0, 0);
    for (int i = 0; i < n; ++i) cout << useless[i] << ' ' << ans[i] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
