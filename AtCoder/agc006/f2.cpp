#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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

int brute(int n, int m, vector<vector<int>> g) {
    set<ii> check;
    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < n; ++i)  {
        for (auto j : g[i]) {
            check.insert({i, j});
            adj[i][j] = 1;
        }
    }
    while (true) {
        bool foi = 0;
        for (int i = 0; i < n; ++i) {
            for (auto j : g[i]) {
                for (auto k : g[j]) {
                    if (adj[k][i] == 0) {
                        foi = 1;
                        adj[k][i] = 1;
                        g[k].pb(i);
                        check.insert({k, i});
                        break;
                    }
                }
                if (foi) break;
            }
            if (foi) break;
        }
        if (foi == 0) break;
    }
    return sz(check);
}

int solve(int n, int m, vector<vector<int>> penis) {
    vector<vector<ii>> g(n);
    for (int i = 0; i < n; ++i) {
        for (auto j : penis[i]) g[i].pb({j, 1}), g[j].pb({i, 2});
    }
    vector<int> vis(n), freq(3), color(n);
    bool p3 = false;
    int e = 0;
    auto explore = [&] (auto&& self, int u) -> bool {
        vis[u] = 1, freq[color[u]]++;
        bool ok = true;
        int z = 0;
        for (auto [v, add] : g[u]) {
            if (add == 1) z |= 1, e++;
            if (add == 2) z |= 2;
            if (vis[v]) {
                ok &= (color[v] == (add + color[u]) % 3);
            } else { 
                color[v] = (add + color[u]) % 3;
                ok &= self(self, v);
            }
        }
        p3 |= (z == 3);
        return ok;
    };

    int ans = 0;

    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            freq[0] = freq[1] = freq[2] = p3 = e = 0;
            bool z = explore(explore, i);
            if (!p3) { 
                ans += e;
            } else {
                if (z) ans += freq[0] * freq[1] + freq[1] * freq[2] + freq[2] * freq[0];
                else ans += (freq[0]+freq[1]+freq[2])*(freq[0]+freq[1]+freq[2]);
            }
        }
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n, m; cin >> n >> m;
    vector<vector<int>> penis(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        penis[u].pb(v);
    }
    cout << solve(n, m, penis) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 20), m = 0;
        vector<vector<int>> g(n);
        vector<ii> edg;
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
            if (rnd(0, 2) == 1) m++, edg.pb({i+1, j+1}), g[i].pb(j);
        }
        int my = solve(n, m, g), ans = brute(n, m, g);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << m << endl;
            for (auto [u, v] : edg) cout << u << " " << v << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
