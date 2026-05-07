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
    int n, q; cin >> n >> q;
    vector<vector<ii>> g(n);
    vector<int> par(n);
    for (int i = 1; i < n; ++i) {
        cin >> par[i]; --par[i];
    }
    for (int i = 1; i < n; ++i) {
        int x; cin >> x;
        g[par[i]].pb({i, x});
    }
    vector<int> ans(q);
    const int lim = 2e18 + 95;
    auto dfs = [&] (auto&& self, int u, int h, vector<ii>& z, int L) -> void {
        if (z.empty()) return;
        if (g[u].empty()) {
            for (auto [penis, i] : z) ans[i] = u;
            return;
        }
        int d = sz(g[u]);
        bool mudou = 0;
        if (L != -1) {
            int _g = gcd(d, L);
            if (L / _g > lim / d) {
                L = -1;
            } else {
                int nL = lcm(d, L);
                if (nL != L) L = nL, mudou = 1;
            }
            // Ld/g > 1e18
            // L/g > 1e18/g
        }
        if (!mudou) {
            auto [val, penis] = z[0];
            auto [v, w] = g[u][(val+h)%d];
            self(self, v, w + h, z, L);
            return;
        } else {
            vector<vector<ii>> penis(d);
            for (auto [val, id] : z) {
                penis[(val+h)%d].pb({val, id});
            }
            for (int i = 0; i < d; ++i) {
                auto [v, w] = g[u][i];
                self(self, v, w+h, penis[i], L);
            }
        }
    };
    vector<ii> qu(q);
    for (int i = 0; i < q; ++i) {
        qu[i].second = i;
        cin >> qu[i].first;
    }
    dfs(dfs, 0, 0, qu, 1);
    for (auto x : ans) cout << x+1 << " ";
    cout << endl;
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
