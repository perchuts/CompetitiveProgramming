#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i], a[i]--, b[i]--;
    vector<vector<ii>> g(2*n);
    for (int i = 0; i < n; ++i) g[a[i]].pb({b[i], i}), g[b[i]].pb({a[i], i});
    vector<int> atv(n, 1);
    while (true) {
        vector<int> vis(2*n);
        auto dfs = [&] (auto&& self, int u, int p) -> int {
            vis[u] = 1;
            for (auto [v, id] : g[u]) {
                if (atv[id] == 0 or v == p) continue;
                if (vis[v] == 1) return id;
                int res = self(self, v, u);
                if (res != -1) return res;
            }
            return -1;
        };
        int kill = -1;
        for (int i = 0; i < 2*n; ++i) {
            if (!vis[i]) {
                int res = dfs(dfs, i, i);
                if (res != -1) {
                    kill = res; break;
                }
            }
        }
        if (kill == -1) break;
        atv[kill] = 0;
    }
    vector<int> ans;
    for (int i = 0; i < n; ++i) if (atv[i] == 1) ans.pb(i);
    cout << sz(ans) << endl;
    for (auto x : ans) cout << x + 1 << ' ';
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
