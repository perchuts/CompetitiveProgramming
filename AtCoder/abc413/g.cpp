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

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<ii> sexo(k);
    for (auto& [x, y] : sexo) cin >> x >> y, --x, --y;
    int K = k + 4;
    vector<int> par(K), lvl(K); iota(all(par), 0);
    map<ii, int> id;
    for (int i = 0; i < k; ++i) id[sexo[i]] = i;
    auto findp = [&] (auto&& self, int u) -> int {
        return par[u] = (par[u] == u ? u : self(self, par[u]));
    };
    auto unite = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) return;
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        if (lvl[u] == lvl[v]) lvl[u]++;
    };
    for (int i = 0; i < k; ++i) {
        auto [x, y] = sexo[i];
        for (auto a : {1, -1, 0}) {
            for (auto b : {1, -1, 0}) {
                int x2 = a + x, y2 = b + y;
                if (id.count({x2, y2})) unite(i, id[{x2, y2}]);
                if (x2 == -1) unite(i, k);
                if (y2 == -1) unite(i, k+1);
                if (x2 == n) unite(i, k+2);
                if (y2 == m) unite(i, k+3);
            }
        }
    }
    for (int i = k; i < k+3; ++i) {
        for (int j = i+1; j <= k+3; ++j) {
            if (i == k and j == k+3) continue;
            if (i == k+1 and j == k+2) continue;
            if (findp(findp, i) == findp(findp, j)) {
                cout << "No" << endl;
                exit(0);
            }
        }
    }
    cout << "Yes" << endl;
}

int32_t main() {_
    int t = 1; //cin >> t;
    while(t--) solve();
}
