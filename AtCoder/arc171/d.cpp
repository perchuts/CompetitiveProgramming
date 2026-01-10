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
    int p, b, n, m; cin >> p >> b >> n >> m;
    // if p is sufficiently big, we are done, i.e. p > N we win
    if (p > n) {
        cout << "Yes" << endl;
        exit(0);
    }
    // P = 2, 3, 5, 7, 11, 13
    n++;
    vector<int> l(m), r(m);
    vector<int> good(1<<n, 1), dp(1<<n);
    vector<int> adj(n+1);
    for (int i = 0; i < m; ++i) cin >> l[i] >> r[i], adj[l[i]-1] += (1 << r[i]), adj[r[i]] += (1 << (l[i]-1));
    for (int i = 1; i < (1 << n); ++i) {
        int choice = -1;
        for (int j = 0; j < n; ++j) if (i >> j & 1) choice = j;
        good[i] = good[i-(1<<choice)] & ((adj[choice] & i) == 0);
        if (good[i]) dp[i] = 1;
        else {
            dp[i] = inf;
            for (int j = (i-1)&i; j; j = (j-1)&i) {
                if (good[j]) ckmin(dp[i], dp[i-j] + 1);
            }
        }
    }
    cout << (dp.back() <= p ? "Yes" : "No") << endl;
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
