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
int dp[(1<<18)][19][19];
void solve(){
    int n, m; cin >> n >> m;
    vector<int> a(n), freq(1<<m);
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        for (int j = 0; j < m; ++j) if (s[j] == '1') a[i] += (1 << j); 
        freq[a[i]]++;
    }
    for (int i = 0; i < (1 << m); ++i) dp[i][0][0] = freq[i];
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j <= m; ++j) {
            int p = (1 << (i-1));
            for (int mask = 0; mask < (1 << m); ++mask) {
                dp[mask][i][j] = dp[mask][i-1][j] + (j?dp[mask^p][i-1][j-1]:0);
            }
        }
    }
    int ans = n*m;
    for (int i = 0; i < (1 << m); ++i) {
        int cur = 0;
        for (int j = 0; j <= m; ++j) cur += min(j, m-j) * dp[i][m][j];
        ckmin(ans, cur);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
