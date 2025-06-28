#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
    string s; cin >> s;
    int n = sz(s);
    auto add = [&] (int& x, int y) {
        x += y;
        if (x >= mod) x -= mod;
    };
    vector<vector<int>> ant(n, vector<int>(26, -1));
    vector<vector<int>> prox(n, vector<int>(26, n));
    for (int i = 0; i < n; ++i) {
        if (i) ant[i] = ant[i-1];
        ant[i][s[i]-'a'] = i;
    }
    for (int i = n-1; ~i; --i) {
        if (i+1 < n) prox[i] = prox[i+1];
        prox[i][s[i]-'a'] = i;
    }
    vector dp(n, vector(n, vector(n, 0)));
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j; k < n; ++k) {
                if (s[i] != s[k]) continue;
                if (i == 0 or ant[i-1][s[i]-'a'] == -1) add(dp[i][j][k], (ant[k-1][s[k]-'a'] < j));
                for (int letra = 0; letra < 26 and k+1<n; ++letra) {
                    int i2 = prox[i+1][letra];
                    int k2 = prox[k+1][letra];
                    if (i2 < j and k2 < n) add(dp[i2][j][k2], dp[i][j][k]);
                }
                if (i == j-1) add(ans, dp[i][j][k]);
            }
        }
    }
    // aabab
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
