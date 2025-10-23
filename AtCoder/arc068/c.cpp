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
    vector<ii> v(n);
    vector<vector<int>> g(m+1);
    vector<int> bit(m+1);
    auto insert = [&] (int x) { while (x <= m) bit[x]++, x += x & (-x); };
    auto query = [&] (int x) {
        int ans = 0;
        while (x) ans += bit[x], x -= x & (-x);
        return ans;
    };
    for (auto& [x, y] : v) cin >> x >> y, g[x].pb(y);
    vector<int> ans(m+1, n);
    auto test = [&] (int i, int d) {
        ans[d] -= query(min(m, i+d-1));
    };
    for (int i = m; i; --i) {
        for (int j = 1; j * j <= i; ++j) {
                if (i % j == 0) {
                    test(i, j);
                    if (j * j != i) test(i, i/j);
                }
        }
        for (auto j : g[i]) insert(j);
        //for (int j = 1; j <= m; ++j) cout << query(j) - query(j-1) << ' ';
        //cout << endl;
    }
    for (int i = 1; i <= m; ++i) test(0, i);
    for (int i = 1; i <= m; ++i) cout << ans[i] << endl;
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
