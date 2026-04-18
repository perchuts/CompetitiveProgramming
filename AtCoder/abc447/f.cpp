#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    int ans = 0;
    auto dfs = [&] (auto&& self, int u, int p) -> int {
        vector<int> z;
        for (auto v : g[u]) {
            if (v == p) continue;
            int k = self(self, v, u);
            if (k != -1) z.pb(k);
        }
        sort(rbegin(z), rend(z));
        // finalizar aqui

        int opt = -1;
        if (sz(g[u]) >= 4 and !z.empty()) opt = 1 + z[0];
		else if (sz(g[u]) == 3) {
			if (!z.empty()) ckmax(ans, 1 + z[0]);
			opt = 1;
		}
        if (sz(g[u]) == 2) ckmax(ans, 1);
        else if (sz(g[u]) >= 3) ckmax(opt, 1);
        ckmax(ans, opt);
        // sou apenas o bicho do meio
        if (sz(z) >= 2 and sz(g[u]) >= 4) ckmax(ans, z[0] + z[1] + 1);
        return opt;
    };
    dfs(dfs, 0, 0);
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
