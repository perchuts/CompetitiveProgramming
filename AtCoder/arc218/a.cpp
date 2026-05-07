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
const int mod = (119<<23)+1;
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
    vector<vector<int>> cnt(n*m);
    vector<vector<int>> a(n, vector<int>(m));
    for (auto& x : a) for (auto& y : x) cin >> y, --y;
    for (int i = 0; i < n; ++i) {
        sort(all(a[i]));
        for (int l = 0, r = 0; r != m; l = r) {
            while (r != m and a[i][r] == a[i][l]) r++;
            cnt[a[i][l]].pb(r-l);
        }
    }
    vector<int> pot(n+1, 1);
    for (int i = 1; i <= n; ++i) pot[i] = m * pot[i-1] % mod;
    int ans = 0;
    for (int i = 0; i < n*m; ++i) {
        vector<int> dp(n+1);
        dp[0] = 1;
        for (auto x : cnt[i]) {
            vector<int> ndp(n+1);
            ndp[0] = dp[0] * (m-x) % mod;
            for (int j = 1; j <= n; ++j) ndp[j] = (dp[j] * (m-x) + x*dp[j-1]) % mod;
            swap(dp, ndp);
        }
        int nao = n - sz(cnt[i]);
        for (int j = 1; j <= n; ++j) ans = (ans + pot[nao] * dp[j]) % mod;  
    }
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
