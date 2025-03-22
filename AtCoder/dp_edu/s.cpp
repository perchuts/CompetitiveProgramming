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
    int d; cin >> d;
    vector<int> dp(d);
    int eu = 0;
    for (int i = 0; i < sz(s); ++i) {
        vector<int> ndp(d);
        int digit = s[i] - '0';
        for (int k = 0; k < 10; ++k) {
            for (int j = 0; j < d; ++j) {
                int nval = (k + j) % d;
                ndp[nval] = (ndp[nval] + dp[j]) % mod;
                if (min(i, k) and j == 0) ndp[nval] = (ndp[nval] + 1) % mod;
            }
            int nval = (k + eu) % d;
            if (k < digit and max(i, k)) ndp[nval] = (ndp[nval] + 1) % mod;
        }
        swap(dp, ndp);
        eu = (eu + digit) % d;
    }
    dp[eu] = (dp[eu] + 1) % mod;
    cout << dp[0] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
