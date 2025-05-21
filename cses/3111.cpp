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
    if (n == 1) {
        // fucker
        cout << 0 << endl;
        exit(0);
    }
    vector<iii> edg(n-1);
    for (auto& [x, y, z] : edg) cin >> y >> z >> x, --y, --z;
    sort(rbegin(edg), rend(edg));
    int ans = 0;
    vector<int> par(n), lvl(n, 1);
    iota(all(par), 0);
    auto findp = [&] (auto&& self, int u) -> int {
        return par[u] = (par[u] == u ? u : self(self, par[u]));
    };
    auto merge = [&] (int u, int v, int k) {
        u = findp(findp, u), v = findp(findp, v);
        assert(u != v);
        ans += lvl[u] * lvl[v] * k;
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        lvl[u] += lvl[v];
    };
    for (auto [x, u, v] : edg) merge(u, v, x);
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
