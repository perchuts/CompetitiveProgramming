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

void solve(){
    string s; cin >> s;
    int n = sz(s);
    vector<int> dp(n+1), occ(26);
    for (int i = 1; i <= n; ++i) {
        if (i != 1 and s[i-2] == s[i-1]) dp[i] = (i>=3?dp[i-2]-dp[i-3]+mod:dp[i-2]);
        else dp[i] = (dp[max(0LL, i-2)] + mod - dp[max(0LL, occ[s[i-1]-'a']-2)]) % mod;
        if (occ[s[i-1]-'a'] == 0) dp[i] = (dp[i]+1) % mod;
        dp[i] = (dp[i] + dp[i-1]) % mod;
        occ[s[i-1]-'a'] = i;
    }
    cout << dp[n] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
