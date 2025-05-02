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
    vector<vector<int>> v(3, vector<int>(m));
    for (int i = 0; i < m; ++i) cin >> v[0][i] >> v[1][i] >> v[2][i], --v[0][i], --v[1][i];
    vector<int> ans(n);
    for (int bit = 0; bit < 60; ++bit) {
        vector<int> par(2*n), lvl(2*n), real(2*n), solved(2*n);
        auto findp = [&] (auto&& self, int u) -> int {
            return par[u] = (u == par[u] ? u : self(self, par[u]));
        };
        for (int i = 0; i < 2*n; ++i) par[i] = i, real[i] = (i < n);
        auto unite = [&] (int u, int v) {
            u = findp(findp, u), v = findp(findp, v);
            if (u == v) return;
            if (lvl[u] < lvl[v]) swap(u, v);
            par[v] = u, real[u] += real[v];
            if (lvl[u] == lvl[v]) lvl[u]++;
        };
        for (int i = 0; i < m; ++i) {
            if (v[2][i] >> bit & 1) unite(v[0][i] + n, v[1][i]), unite(v[0][i], v[1][i]+n);
            else unite(v[0][i], v[1][i]), unite(v[1][i]+n, v[0][i]+n);
        }
        for (int i = 0; i < n; ++i) {
            if (findp(findp, i) == findp(findp, i+n)) {
                cout << -1 << endl;
                exit(0);
            }
        }
        for (int i = 0; i < n; ++i) {
            int x1 = par[i], x2 = par[i+n];
            if (solved[x1] or solved[x2]) continue;
            if (real[x1] <= real[x2]) solved[x1] = 1;
            else solved[x2] = 1;
        }
        for (int i = 0; i < n; ++i) if (solved[par[i]]) ans[i] += (1LL << bit);
    }
    for (auto x : ans) cout << x << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
