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
    string s; int k; cin >> s >> k;
    int n = sz(s);
    vector<vector<int>> dp(n+2, vector<int>(n+2));
    for (int l = n; l >= 1; --l) {
        for (int r = l; r <= n; ++r) {
            dp[l][r] = 1 + dp[l+1][r];
            if (s[l-1] != 'o') continue;
            for (int w = l+1; w <= r; ++w) {
                if (dp[l+1][w-1] == 0 and s[w-1] == 'f') ckmin(dp[l][r], max(0, dp[w+1][r]-k));
            }
        }
    }
    cout << dp[1][n] << endl;
}

int32_t main(){_
    solve();
}
