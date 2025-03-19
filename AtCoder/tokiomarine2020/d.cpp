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
    vector<int> v(n+1), w(n+1);
    for (int i = 1; i <= n; ++i) cin >> v[i] >> w[i];
    int q; cin >> q;
    vector<vector<ii>> queries(n+1);
    vector<int> ans(q);
    for (int i = 0; i < q; ++i) {
        int x, v; cin >> x >> v;
        queries[x].pb({v, i});
    }
    vector<int> vals;
    vector<ii> msb(1<<20), curdp = msb;
    msb[1] = {1, 0};
    for (int i = 2; i < (1 << 20); ++i) msb[i] = {msb[i/2].first * 2, msb[i/2].second + 1};
    int MAX = 100000, lim = 9;
    vector<int> pre(MAX+1);
    auto dfs = [&] (auto&& self, int u) -> void {
        if (u > n) return;
        vals.pb(u);
        if (sz(vals) <= lim) {
            for (int i = 1; i < (1 << sz(vals)); ++i) {
                auto [take, id] = msb[i];
                curdp[i] = curdp[i-take];
                curdp[i].first += w[vals[id]];
                curdp[i].second += v[vals[id]];
            }
            for (auto [x, idq] : queries[u]) {
                for (int i = 1; i < (1 << sz(vals)); ++i) if (curdp[i].first <= x) ckmax(ans[idq], curdp[i].second);
            }
        } else {
            for (int i = 1; i < (1 << (sz(vals)-lim)); ++i) {
                auto [take, id] = msb[i];
                curdp[i] = curdp[i-take];
                curdp[i].first += w[vals[id+lim]];
                curdp[i].second += v[vals[id+lim]];
            }
            for (auto [x, idq] : queries[u]) {
                for (int i = 0; i < (1 << (sz(vals)-lim)); ++i) if (curdp[i].first <= x) {
                    ckmax(ans[idq], curdp[i].second + pre[x-curdp[i].first]);
                }
            }
        }
        if (sz(vals) == lim) {
            for (int i = 1; i <= MAX; ++i) pre[i] = 0;
            for (int i = 1; i < (1 << lim); ++i) if (curdp[i].first <= MAX) ckmax(pre[curdp[i].first], curdp[i].second);
            for (int i = 1; i <= MAX; ++i) ckmax(pre[i], pre[i-1]);
        }
        self(self, 2*u), self(self, 2*u+1);
        vals.pop_back();
    };
    dfs(dfs, 1);
    for (auto x : ans) cout << x << endl;

}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
