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
    int n, q; cin >> n >> q;
    vector<map<int, int>> mp(n);
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        --x;
        mp[i][x]++;
    }
    vector<int> par(n); iota(all(par), 0);
    auto findp = [&] (auto&& self, int u) -> int { return par[u] = (par[u] == u ? u : self(self, par[u])); };
    auto merge = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) return;
        if (sz(mp[u]) < sz(mp[v])) swap(u, v);
        for (auto [x, y] : mp[v]) mp[u][x] += y;
        par[v] = u;
    };
    while (q--) {
        int op, x, y; cin >> op >> x >> y; --x, --y;
        if (op == 1) merge(x, y);
        else {
            x = findp(findp, x);
            if (!mp[x].count(y)) cout << 0 << endl;
            else cout << mp[x][y] << endl;
        }
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
