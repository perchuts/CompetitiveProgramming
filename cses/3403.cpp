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
    int n, m; cin >> n >> m;
    vector<vector<int>> dp(n+1, vector<int>(m+1));
    vector<int> a(n+1), b(m+1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= m; ++i) cin >> b[i];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            ckmax(dp[i][j], dp[i][j-1]);
            ckmax(dp[i][j], dp[i-1][j]);
            if (a[i] == b[j]) dp[i][j] = dp[i-1][j-1] + 1;
        }
    }
    cout << dp[n][m] << endl;
    int want = dp[n][m], i = n, j = m;
    vector<int> sexo;
    while (want) {
        if (a[i] == b[j]) sexo.pb(a[i]), --i, --j, --want;
        else if (dp[i-1][j] > dp[i][j-1]) --i;
        else --j;
    }
    reverse(all(sexo));
    for (auto x : sexo) cout << x << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
