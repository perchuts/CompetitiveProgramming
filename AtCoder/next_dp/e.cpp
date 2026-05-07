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
    int n, m, q; cin >> n >> m >> q;
    vector<int> fim(n+2, n+1);
    for (int i = 1; i <= m; ++i) {
        int a, b; cin >> a >> b;
        ckmin(fim[a], b);
    }
    vector<vector<int>> sp(18, vector<int>(n+2)), ev(n+3);
    for (int i = 1; i <= n; ++i) ev[fim[i]+1].pb(i);
    vector<int> seta(n+2, n+1), lst(n+2, n+1);
    for (int i = n; i >= 1; --i) {
        lst[i] = lst[i+1];
        if (fim[i] < fim[lst[i]]) lst[i] = i;
        for (auto x : ev[i]) seta[x] = lst[i];
    }
    sp[0] = seta;
    for (int i = 1; i < 18; ++i) {
        for (int j = 1; j <= n+1; ++j) {
            sp[i][j] = sp[i-1][sp[i-1][j]];
        }
    }
    while (q--) {
        int l, r; cin >> l >> r;
        int cur = lst[l], ans = 0;
        for (int i = 17; ~i; --i) {
            if (sp[i][cur] <= r) ans += (1 << i), cur = sp[i][cur];
        }
        if (fim[cur] <= r) ans++;
        cout << ans << endl;
    }

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
