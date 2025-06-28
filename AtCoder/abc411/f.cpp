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
    vector<set<int>> sexo(n);
    for (auto& [x, y] : edg) cin >> x >> y, --x, --y, sexo[x].insert(y), sexo[y].insert(x);
    int q; cin >> q;
    vector<int> par(n), lvl(n); iota(all(par), 0);
    for (int i = 0; i < n; ++i) lvl[i] = sz(sexo[i]);
    auto findp = [&] (auto&& self, int u) -> int {
        return (par[u] == u ? u : self(self, par[u]));
    };
    int ans = m;
    while (q--) {
        int x; cin >> x; --x;
        auto [u, v] = edg[x];
        u = findp(findp, u), v = findp(findp, v);
        if (u != v) {
            if (sz(sexo[u]) < sz(sexo[v])) swap(u, v);
            par[v] = u;
            for (auto x : sexo[v]) {
                if (x == u) continue;
                assert(par[x] == x);
                sexo[x].insert(u);
                sexo[x].erase(v);
            }
            sexo[u].erase(v);
            for (auto x : sexo[v]) {
                if (x == u or sexo[u].find(x) != end(sexo[u])) ans--;
                else sexo[u].insert(x);
            }
        }
        cout << ans << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
