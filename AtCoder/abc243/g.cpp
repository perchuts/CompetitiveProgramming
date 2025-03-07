#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ull

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

int dp[maxn];

void solve(){
    int n; cin >> n;
    // posso ir em 1, 2 passos, ou >= 3 passos. se eu for em >= 3 passos, vou estar em no maximo N^1/4. brutar esse cara 
    int l = 1, r = 3e9, sqr = 1;
    while (l <= r) {
        int md = l + (r-l+1)/2;
        if (md*md <= n) sqr = md, l = md+1;
        else r = md-1;
    }
    int ans = sqr;
    for (int j = 2; j * j <= sqr; ++j) ans += (sqr + 1 - j * j) * dp[j];
    cout << ans << endl;
}

int32_t main(){_
    dp[1] = 1;
    for (int i = 2; i < maxn; ++i) for (int j = 1; j * j <= i; ++j) dp[i] += dp[j];
    int t = 1; cin >> t;
    while(t--) solve();
}
