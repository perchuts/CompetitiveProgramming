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
    int n, k; cin >> n >> k;
    // 2, 3, 5, 7
    vector<int> vals = {2, 3, 5, 7};
    vector<vector<int>> pots(sz(vals));
    for (int i = 0; i < sz(vals); ++i) {
        pots[i].pb(1);
        while (pots[i].back() * vals[i] <= 1e18) pots[i].pb(pots[i].back() * vals[i]);
    }
    vector ok(65, vector(65, vector(65, vector(65, false))));
    for (int i = 0; i < sz(pots[0]); ++i) {
        int x = pots[0][i];
        for (int j = 0; pots[1][j] <= k / x; ++j) {
            int y = x * pots[1][j];
            for (int l = 0; pots[2][l] <= k / y; ++l) {
                int z = y * pots[2][l];
                for (int m = 0; pots[3][m] <= k / z; ++m) ok[i][j][l][m] = 1;
            }
        }
    }
    vector dp(4, vector(3, vector(2, vector(2, vector(2, vector(2, 0LL))))));
    vector<int> nval;
    int cc = n;
    for (int i = 0; i <= 18; ++i) nval.pb(cc%10), cc /= 10;
    int start = 18;
    while (nval[start] == 0) start--;
    vector<vector<int>> incr(10, vector<int>(4));
    for (int i = 1; i <= 9; ++i) {
        int cur = i;
        while (cur % 2 == 0) incr[i][0]++, cur /= 2;
        while (cur % 3 == 0) incr[i][1]++, cur /= 3;
        while (cur % 5 == 0) incr[i][2]++, cur /= 5;
        while (cur % 7 == 0) incr[i][3]++, cur /= 7;
    }
    dp[0][0][0][0][1][0] = 1;
    for (int d = start; ~d; --d) {
        int cur_d = nval[d], tt = start-d+1; 
        vector ndp(3*tt+4, vector(2*tt+3, vector(tt+2, vector(tt+2, vector(2, vector(2, 0LL))))));
        for (int i = 0; i <= 3*tt; ++i) for (int j = 0; j <= 2*tt; ++j) for (int l = 0; l <= tt; ++l) for (int m = 0; m <= tt; ++m) {
            for (int zero = 0; zero < 2; ++zero) {
                auto& DP0 = ndp[i][j][l][m][0][zero];
                auto& DP1 = ndp[i][j][l][m][1][zero];
                for (int cur = 1; cur <= 9; ++cur) {
                    int i2 = i - incr[cur][0];
                    int j2 = j - incr[cur][1];
                    int l2 = l - incr[cur][2];
                    int m2 = m - incr[cur][3];
                    if (min({i2, j2, l2, m2}) < 0) continue;
                    DP0 += dp[i2][j2][l2][m2][0][zero];
                    if (cur == cur_d) DP1 += dp[i2][j2][l2][m2][1][zero];
                    if (cur_d > cur) DP0 += dp[i2][j2][l2][m2][1][zero];
                    if (i2+j2+l2+m2 == 0 and !zero and d != start) DP0++;
                }
				// o zero precisa transicionar de um lugar com numeros que existem!
                if (zero) {
                    DP0 += dp[i][j][l][m][0][1] + dp[i][j][l][m][0][0];
                    if (0 == cur_d) DP1 += dp[i][j][l][m][1][1] + dp[i][j][l][m][1][0];
                    else if (d != start) DP0 += dp[i][j][l][m][1][1] + dp[i][j][l][m][1][0];
                }
            }
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for (int i = 0; i < sz(dp); ++i) for (int j = 0; j < sz(dp[0]); ++j) for (int l = 0; l < sz(dp[0][0]); ++l) for (int m = 0; m < sz(dp[0][0][0]); ++m) {
		int add = 0;
        add += dp[i][j][l][m][1][1];
        add += dp[i][j][l][m][0][1];
		if (add) ans += add;
        if (ok[i][j][l][m]) {
            ans += dp[i][j][l][m][1][0];
            ans += dp[i][j][l][m][0][0];
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
