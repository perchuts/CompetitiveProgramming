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
    vector<int> p(n), deg(n);
    vector<vector<int>> g(n);
    for (auto& x : p) cin >> x, --x, deg[x]++;
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (deg[i] == 0) q.push(i);
        g[p[i]].pb(i);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        deg[p[u]]--;
        if (deg[p[u]] == 0) q.push(p[u]);
    }
    int ans = (p[0] != 0);
    auto go = [&] (auto&& self, int u) -> int {
        int depth = 0;
        for (auto v : g[u]) {
            if (v == 0) continue;
            int x =  self(self, v) + 1;
            if (x == k and u != 0) ans++;
            else ckmax(depth, x);
        }
        return depth;
    };
    go(go, 0);
    cout << ans << endl;
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
