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
    vector<int> ans(m), par(n), lvl(n);
    for (int i = 0; i < n; ++i) par[i] = i, lvl[i] = 1;
    for (auto& [x, y] : edg) cin >> x >> y, --x, --y;
    int cur = n * (n-1) / 2;
    auto findp = [&] (auto&& self, int u) -> int {
        return par[u] = (par[u] == u ? u : self(self, par[u]));
    };
    auto unite = [&] (int x, int y) {
        x = findp(findp, x), y = findp(findp, y);
        if (x == y) return;
        if (lvl[x] < lvl[y]) swap(x, y);
        par[y] = x;
        cur -= lvl[x] * lvl[y];
        lvl[x] += lvl[y];
    };
    for (int i = m-1; ~i; --i) {
        ans[i] = cur;
        unite(edg[i].first, edg[i].second);
    }
    for (auto x : ans) cout << x << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
