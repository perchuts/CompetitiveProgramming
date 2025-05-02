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
    vector<ii> pts(n);
    for (auto& [x, y] : pts) cin >> x >> y;
    double eps = 1e-8;
    auto possible = [&] (double r) {
        vector<int> par(n), lvl(n), can(n); iota(all(par), 0);
        auto findp = [&] (auto&& self, int u) -> int {
            return par[u] = (par[u] == u ? u : self(self, par[u]));
        };
        for (int i = 0; i < n; ++i) {
            if (abs(-100-pts[i].second) < r-eps) can[i] |= 1;
            if (abs(100-pts[i].second) < r-eps) can[i] |= 2;
        }
        auto merge = [&] (int u, int v) {
            u = findp(findp, u), v = findp(findp, v);
            if (u == v) return;
            if (lvl[u] < lvl[v]) swap(u, v);
            par[v] = u;
            if (lvl[u] == lvl[v]) lvl[u]++;
            can[u] |= can[v];
        };
        for (int i = 0; i < n; ++i) for (int j = i+1; j < n; ++j) {
            double h = hypot(pts[i].first-pts[j].first, pts[i].second-pts[j].second);
            if (h < r-eps) merge(i, j);
        }
        for (int i = 0; i < n; ++i) if (can[i] == 3) return false;
        return true;
    };
    double l = 0, r = 200;
    for (int i = 0; i < 50; ++i) {
        double md = (l+r)/2;
        if (possible(md)) l = md;
        else r = md;
    }
    cout << fixed << setprecision(10) << l/2 << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
