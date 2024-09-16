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
const int maxn = 1e6+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

int fexp(int b, int e) {
    int ans = 1, p = b;
    while (e) {
        if (e&1) ans = ans * p % mod;
        p = p * p % mod, e /= 2;
    }
    return ans;
}

int my(int n, int m, string s) {
    vector<vector<int>> dp(n+m+1, vector<int>(2));
    
    dp[0][0] = 1;
    for (int j = 1; j <= m; ++j) {
        for (int i = 0; i <= n+m; ++i) {
            // colocar
			dp[i][j&1] = 0;
            if (i != 0) dp[i][j&1] = (2 * dp[i-1][(j-1)&1]) % mod;
            // apagar
            if (i != n+m) dp[i][j&1] = (dp[i][j&1] + dp[i+1][(j-1)&1]) % mod;
			if (i == 0) dp[i][j&1] = (dp[i][j&1] + dp[i][(j-1)&1]) % mod;
        }
    }
    return (dp[n][m&1] * fexp(2, (mod-2)*n)) % mod;
}

mt19937 rng(time(0));

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
int32_t main(){
  int n, m; cin >> m;
  string s; cin >> s;
  n = sz(s);
  cout << my(n, m, s) << endl;
}
