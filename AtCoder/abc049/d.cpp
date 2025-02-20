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
    int n, m1, m2; cin >> n >> m1 >> m2;
    vector<vector<int>> par(2, vector<int>(n)), lvl(2, vector<int>(n));
    auto findp = [&] (auto&& self, int x, int u) -> int {
        return par[x][u] = (par[x][u] == u ? u : self(self, x, par[x][u]));
    };
    auto unite = [&] (int x, int u, int v) {
        u = findp(findp, x, u), v = findp(findp, x, v);
        if (u == v) return;
        if (lvl[x][u] < lvl[x][v]) swap(u, v);
        par[x][v] = u;
        if (lvl[x][u] == lvl[x][v]) lvl[x][u]++;
    };
    iota(all(par[0]), 0);
    iota(all(par[1]), 0);
    for (int i = 0; i < m1+m2; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        unite((i>=m1), u, v);
    }
    vector<vector<int>> comps(n);
    for (int i = 0; i < n; ++i) comps[findp(findp, 0, i)].pb(i);
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        map<int, int> cnt;
        for (auto x : comps[i]) cnt[findp(findp, 1, x)]++;
        for (auto x : comps[i]) ans[x] = cnt[findp(findp, 1, x)];
    }
    for (auto x : ans) cout << x << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
