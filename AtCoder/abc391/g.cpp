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

void solve(){
    int n, m; cin >> n >> m;
    string s; cin >> s;
    vector<vector<int>> tr(1<<n);
    for (int i = 0; i < (1<<n); ++i) {
        vector<int> ldp = {0};
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) ldp.pb(ldp.back()+1);
            else ldp.pb(ldp.back());
        }
        for (int j = 0; j < 26; ++j) { 
            vector<int> ndp(n+1);
            for (int k = 1; k <= n; ++k) {
                if (s[k-1] == char('a'+j)) ndp[k] = ldp[k-1]+1; 
                else ndp[k] = max(ndp[k-1], ldp[k]);
            }
            int m = 0;
            for (int k = 0; k < n; ++k) if (ndp[k+1] - ndp[k]) m += (1 << k);
            tr[m].pb(i);
        }
    }
    vector<int> dp(1<<n), ans(n+1);
    dp[0] = 1;
    for (int i = 1; i <= m; ++i) {
        vector<int> ndp(1<<n);
        for (int m = 0; m < (1 << n); ++m) {
            for (auto m2 : tr[m]) ndp[m] = (ndp[m] + dp[m2]) % mod;
        }
        swap(dp, ndp);
    }
    for (int i = 0; i < (1 << n); ++i) ans[__builtin_popcount(i)] += dp[i];
    for (auto x : ans) cout << x % mod << ' ';
    cout << endl;
}

int32_t main(){_
    solve();
}
