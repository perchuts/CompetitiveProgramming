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
    int n, k; cin >> n >> k;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<int> ans(n, -1), lvl(n), lx(n), rx(n), quem(n+1), par(n);
    int tt = 0;
    vector<set<int>> bichos(n+1);
    auto pre = [&] (auto&& self, int u, int p) -> void {
        lvl[u] = 1 + lvl[p];
        lx[u] = ++tt;
        quem[lx[u]] = u;
        par[u] = p;
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
        rx[u] = tt;
        bichos[lvl[u]].insert(lx[u]);
    };
    pre(pre, 0, 0);
    bichos[1].clear();
    queue<int> q;
    q.push(0);
    ans[0] = 0;
    while (!q.empty()) {
        auto u = q.front(); q.pop();
        int cur = u;
        int x1 = rx[cur], x2 = rx[cur]+1;
        while (true) {
            // k = lvl[u] + lvl[v] - 2 * lvl[cur]
            // lvl[v] = 2 * lvl[cur] + k - lvl[u]
            int want = 2 * lvl[cur] + k - lvl[u];
            // antes
            while (want <= n) {
                auto it = bichos[want].lower_bound(lx[cur]);
                if (it == bichos[want].end() or (*it) > x1) break;
                int v = quem[*it];
                bichos[want].erase(it);
                q.push(v);
                ans[v] = 1 + ans[u];
            }
            // depois
            while (want <= n) {
                auto it = bichos[want].lower_bound(x2);
                if (it == bichos[want].end() or (*it) > rx[cur]) break;
                int v = quem[*it];
                bichos[want].erase(it);
                q.push(v);
                ans[v] = 1 + ans[u];
            }
            if (cur == 0 or lvl[u] - lvl[cur] == k) break;
            x1 = lx[cur]-1;
            x2 = rx[cur]+1;
            cur = par[cur];
        }
    }
    for (int i = 1; i < n; ++i) cout << ans[i] << ' ';

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
