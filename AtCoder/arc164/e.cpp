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
    int n, q; cin >> n >> q;
    vector<int> lx(q), rx(q);
    for (int i = 0; i < q; ++i) cin >> lx[i] >> rx[i];
    vector<vector<ii>> dp(n+1, vector<ii>(n+1, {-inf, 0}));
    for (int l = n; l >= 1; --l) {
        for (int r = l; r <= n; ++r) { 
            dp[l][r] = {-1e18, 0};
            bool nice = 1;
            int tem = 0;
            for (int i = 0; i < q; ++i) {
                if (rx[i] < l or r < lx[i]) continue;
                if (lx[i] <= l and r <= rx[i]) {
                    tem++;
                    continue;
                }
                nice = 0;
            }
            if (!nice) {
                dp[l][r] = {1e18, 0};
                // -> nao sei tratar o caso 3
                for (int k = l; k < r; ++k) {
                    auto tmp = max(dp[l][k], dp[k+1][r]);
                    tmp.first++;
                    if (dp[l][k].first == dp[k+1][r].first) tmp.second = dp[l][k].second + dp[k+1][r].second - (dp[l][k].first==0?tem:0);
                    ckmin(dp[l][r], tmp);
                }
            } else if (tem) dp[l][r] = {0, tem};
        }
    }
    cout << dp[1][n].first << ' ' << (1+(dp[1][n].first!=0))*dp[1][n].second << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
