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
    int n, m; cin >> n >> m;
    vector<ii> edg(m);
    vector<int> mark(m);
    for (auto& [x, y] : edg) cin >> x >> y, --x, --y;
    int m2; cin >> m2;
    vector<int> usar(m2);
    for (auto& x : usar) cin >> x, --x, mark[x] = 1;
    vector<int> par(n), lvl(n);
    auto findp = [&] (auto&& self, int u) -> int {
        return par[u] = (par[u] == u ? u : self(self, par[u]));
    };
    auto unite = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) return;
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        if (lvl[u] == lvl[v]) lvl[u]++;
    };
    iota(all(par), 0);
    for (int i = 0; i < m; ++i) if (!mark[i]) unite(edg[i].first, edg[i].second);
    vector<int> deg(n);
    for (int i = 0; i < m; ++i) if (mark[i]) {
        int u = findp(findp, edg[i].first), v = findp(findp, edg[i].second);
        if (u != v) deg[u]++, deg[v]++;
    }
    int cnt = 0;
    for (int i = 0; i < n; ++i) cnt += (deg[i] & 1);
    cout << (cnt == 0 or cnt == 2 ? "Yes" : "No") << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
