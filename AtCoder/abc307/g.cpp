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
    int n; cin >> n;
    vector<int> a(n), pref(n+1);
    for (auto& x : a) cin >> x;
    for (int i = 1; i <= n; ++i) pref[i] = pref[i-1] + a[i-1];
    int m = pref.back() % n, s = pref.back(), low;
    if (s >= 0) low = s / n;
    else low = (s-n+1)/n;
    m = (m + n) % n;
    vector dp(n+1, vector(m+1, inf*inf));
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            int ai = pref[i] - (i-1-j)*low - j*(low+1);
            ckmin(dp[i][j], dp[i-1][j] + abs(low-ai));
            if (j) {
                ai = pref[i] - (i-j)*low - (j-1)*(low+1);
                ckmin(dp[i][j], dp[i-1][j-1] + abs(low+1-ai));
            }
        }
    }
    cout << dp[n][m] << endl;    
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
