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

    int n; cin >> n;
    vector<vector<int>> g(n);

    for (int i = 0; i < n-1; ++i) { int u, v; cin >> u >> v; --u, --v; g[u].pb(v), g[v].pb(u); }

    vector<int> val(n, inf);

    int k; cin >> k;

    for (int i = 0; i < k; ++i) { int x, y; cin >> x >> y; --x; val[x] = y; }

    vector<array<int, 3>> ranges(n);
    
    auto dfs = [&] (auto&& self, int u, int p) -> void {

        ranges[u][2] = 3, ranges[u][0] = -inf, ranges[u][1] = inf;

        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            int l = ranges[v][0], r = ranges[v][1];
            l--, r++;
            ckmax(ranges[u][0], l);
            ckmin(ranges[u][1], r);
            ranges[u][2] &= ranges[v][2];
        }

        if (ranges[u][2] == 0 or ranges[u][0] > ranges[u][1]) {
            cout << "No" << endl;
            exit(0);
        }

        if (ranges[u][2] == 1) ranges[u][2] = 2;
        else if (ranges[u][2] == 2) ranges[u][2] = 1;

        if (val[u] != inf) {
            int type = (val[u] % 2);
            if (ranges[u][2] >> type & 1) {}
            else {
                cout << "No" << endl;
                exit(0);
            }
            if (val[u] < ranges[u][0] or ranges[u][1] < val[u]) {
                cout << "No" << endl;
                exit(0);
            }
            ranges[u][0] = ranges[u][1] = val[u];
            ranges[u][2] = (1 << type);
        }
    };
    int root;
    for (int i = 0; i < n; ++i) if (val[i] != inf) root = i;
    dfs(dfs, root, root);
    cout << "Yes" << endl;
    auto build = [&] (auto&& self, int u, int p) -> void {
        if (val[u] == inf) {
            if (ranges[u][0] <= val[p]-1 and val[p]-1 <= ranges[u][1]) val[u] = val[p]-1;
            else val[u] = val[p]+1;
        }
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
    };
    build(build, root, root);
    for (int i = 0; i < n; ++i) cout << val[i] << endl;

}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
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
