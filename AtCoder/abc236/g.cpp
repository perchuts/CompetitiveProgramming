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
    int n, t, l; cin >> n >> t >> l;
    vector<vector<int>> id(n, vector<int>(n, inf));
    for (int i = 0; i < t; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        id[u][v] = i;
    }
    auto mult = [&] (vector<vector<int>> a, vector<vector<int>> b) {
        vector<vector<int>> c(n, vector<int>(n, inf));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    ckmin(c[i][j], max(a[i][k], b[k][j]));
                }
            }
        }
        return c;
    };
    vector<vector<int>> ans(n, vector<int>(n, inf));
    for (int i = 0; i < n; ++i) ans[i][i] = 0;
    while (l) {
        if (l&1) ans = mult(ans, id);
        id = mult(id, id), l /= 2;
    }
    for (int i = 0; i < n; ++i) cout << (ans[0][i] == inf ? -1 : ans[0][i]+1) << " \n"[i==n-1];
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
