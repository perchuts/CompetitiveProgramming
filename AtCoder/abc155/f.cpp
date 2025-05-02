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
    vector<int> a(n), b(n), ord(n); iota(all(ord), 0);
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i];
    sort(all(ord), [&] (int x, int y) { return a[x] < a[y]; });
    vector<ii> intr(m);
    for (auto& [x, y] : intr) {
        cin >> x >> y;
        int l = 0, r = n-1, px = n;
        while (l <= r) {
            int md = l + (r-l+1)/2;
            if (x <= a[ord[md]]) px = md, r = md-1;
            else l = md+1;
        }
        x = px;
        l = 0, r = n-1; int py = n;
        while (l <= r) {
            int md = l + (r-l+1)/2;
            if (a[ord[md]] <= y) py = md, l = md+1;
            else r = md-1;
        }
        y = py;
        if (x == n or y == n or x > y) x = y = -1;
    }
    vector<int> b2(n);
    b2[0] = b[ord[0]];
    for (int i = 1; i < n; ++i) b2[i] = b[ord[i]] ^ b[ord[i-1]];
    b2.pb(b[ord.back()]);
    vector<vector<ii>> g(n+1);
    int id = 0;
    for (auto [x, y] : intr) {
        if (x != -1) g[x].pb({y+1, id}), g[y+1].pb({x, id});
        id++;
    }
    vector<int> ans, vis(n+1);
    auto dfs = [&] (auto&& self, int u) -> int {
        vis[u] = 1;
        int sum = b2[u];
        for (auto [v, idx] : g[u]) {
            if (vis[v]) continue;
            int baio = self(self, v);
            if (baio) ans.pb(idx), sum ^= 1;
        }
        return sum;
    };
    for (int i = 0; i <= n; ++i) {
        if (!vis[i]) {
            if (dfs(dfs, i)) {
                cout << -1 << endl;
                exit(0);
            }
        }
    }
    cout << sz(ans) << endl;
    sort(all(ans));
    for (auto x : ans) cout << x + 1 << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
