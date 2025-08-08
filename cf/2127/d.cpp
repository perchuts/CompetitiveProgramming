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
int fat[maxn], ifat[maxn];
void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v; 
        --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    if (n == 2) {
        cout << 2 << endl;
        return;
    }
    vector<int> vis(n, -1);
    auto check = [&] (auto&& self, int u, int p) -> bool {
        for (auto v : g[u]) {
            if (v == p) continue;
            if (vis[v] == -1) {
                vis[v] = vis[u] ^ 1;
                if (!self(self, v, u)) return false;
            } else return false;
        }
        return true;
    };
    vis[0] = 0;
    if (!check(check, 0, 0)) {
        cout << 0 << endl;
        return;
    }
    bool ok = true;
    int random = 2;
    int tot2 = 0;
    for (int i = 0; i < n; ++i) {
        tot2 += (sz(g[i]) >= 2);
        int cnt = 0;
        for (auto v : g[i]) {
            cnt += (sz(g[v]) >= 2);
        }
        if (cnt > 2) ok = false;
        for (int j = 1; j <= sz(g[i]) - cnt; ++j) random = random * j % mod;
    }
    if (!ok) {
        cout << 0 << endl;
        return;
    }
    if (tot2 > 1) random = random * 2 % mod;
    cout << random << endl;
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
