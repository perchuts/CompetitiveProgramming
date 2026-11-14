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
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    vector<vector<int>> ps;
    vector<int> cur(n, -1);
    auto go = [&] (auto&& self, int i, bool foi_imp = 0) -> void {
        if (i == n) { ps.pb(cur); return; }
        if (cur[i] != -1) { self(self, i+1, foi_imp); return; }
        for (int j = i + 1; j < n; ++j) {
            if (cur[j] == -1) { cur[i] = j, cur[j] = i; self(self, i+1, foi_imp); cur[i] = cur[j] = -1; }
        }
        if ((n & 1) and !foi_imp) { cur[i] = i; self(self, i+1, 1); cur[i] = -1; }
    };
    go(go, 0);
    vector<int> nice(1<<m);
    vector<vector<int>> bad(1<<m);
    for (int i = 0; i < (1<<m); ++i) {
        for (int j = 0; j < m; ++j) {
            if (i >> j & 1) {}
            else bad[i].pb(j);
        }
    }
    vector<vector<int>> ok(m, vector<int>(m));
    for (auto p : ps) {

    }
    cout << "NO" << endl;
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
