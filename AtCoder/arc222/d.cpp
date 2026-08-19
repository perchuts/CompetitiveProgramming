#include <bits/stdc++.h>
#define endl '\n'
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

using namespace std;

using ll = long long;

const int inf = 2e9+1;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }

int32_t main() {_
	int n; cin >> n;
	vector<vector<int>> a(2, vector<int>(n));
	for (auto& x : a) for (auto& y : x) cin >> y;
    vector<int> pw(10, 1);
    for (int i = 1; i < 10; ++i) pw[i] = 10 * pw[i-1];
    const int lim = pw[9];
    vector<array<int, 2>> dp(512, {inf, inf});
    dp[0] = {0, 1};
    for (int i = 0; i < n; ++i) {
        vector<array<int, 2>> ndp(512, {inf, inf});
        int opt = inf;
        for (int j = 0; j < (1 << min(10LL, i+1)); ++j) {
            int v = 0;
            for (int k = 1; k < min(10LL, i+1); ++k) v += pw[k] * a[j>>k&1][i-k];
            ckmin(ndp[j&511][0], dp[j/2][(a[j&1][i]+(v%(10*lim)) >= 10*lim)] + ((v+a[j&1][i])/lim)%10);
            ckmin(ndp[j&511][1], dp[j/2][(a[j&1][i]+(v%(10*lim))+lim >= 10*lim)] + ((v+a[j&1][i]+lim)/lim)%10);
            int val = dp[j/2][(a[j&1][i]+(v%(10*lim)) >= 10*lim)];
            for (int k = 0; k <= 9; ++k) val += ((v+a[j&1][i])/pw[k])%10;
            ckmin(opt, val);
        }
		cout << opt << ' ';
        swap(dp, ndp);
    }
}
