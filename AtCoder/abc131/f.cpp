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
    vector<vector<int>> g(maxn);
    int shift = 1e5+10;
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        g[x].pb(shift+y);
        g[shift+y].pb(x);
    }
    vector<int> vis(maxn);
    int ans = -n;
    auto dfs = [&] (auto&& self, int u) -> ii {
        vis[u] = 1;
        int cx = 1, cy = 0;
        for (auto v : g[u]) {
            if (vis[v]) continue;
            auto [aa, bb] = self(self, v);
            swap(aa, bb);
            cx += aa, cy += bb;
        }
        return make_pair(cx, cy);
    };
    for (int i = 0; i < maxn; ++i) {
        if (vis[i]) continue;
        auto [x, y] = dfs(dfs, i);
        ans += x * y;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
