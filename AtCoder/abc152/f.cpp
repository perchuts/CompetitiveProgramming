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
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    int m; cin >> m;
    vector<ii> v(m);
    for (auto& [x, y] : v) cin >> x >> y, --x, --y;
    vector<int> lvl(n), par(n);
    auto pre = [&] (auto&& self, int u, int p) -> void {
        par[u] = p, lvl[u] = 1 + lvl[p];
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
    };
    pre(pre, 0, 0);
    vector<int> mask(n);
    int id = 0;
    for (auto [x, y] : v) {
        while (x != y) {
            if (lvl[x] > lvl[y]) mask[x] |= (1 << id), x = par[x];
            else if (lvl[x] < lvl[y]) mask[y] |= (1 << id), y = par[y];
            else mask[x] |= (1 << id), x = par[x], mask[y] |= (1 << id), y = par[y];
        }
        id++;
    }
    // agora eu basicamente tenho 50 caras, e quero o numero de maneiras de escolher alguns deles de forma q o or de tudo seja todo mundo
    reverse(all(mask)); mask.pop_back(); n--;
    int ans = 0;
    for (int j = 0; j < (1<<m); ++j) {
        int tot = 1;
        for (auto x : mask) {
            if (x & j) {}
            else tot *= 2;
        }
        if (__builtin_popcount(j) & 1) ans -= tot;
        else ans += tot;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
