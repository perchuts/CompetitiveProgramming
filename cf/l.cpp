#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;
	int n, g; cin >> n >> g;
	vector<int> t(n), pr(n+1);
	for (auto& x : t) cin >> x;
	for (int i = 1; i <= n; ++i) pr[i] = pr[i-1] + t[i-1];
	vector<int> dp(n+1, 0);
	int ans = 0;
	for (int step = 1; step * (step + 1) / 2 <= n; ++step) {
		vector<int> ndp(n+1, -1e18);
		for (int i = step; i <= n; ++i) ndp[i] = max(ndp[i-1], dp[i-step] + g - (pr[i] - pr[i-step]));
		swap(dp, ndp);
		ans = max(ans, dp.back());
	}
	cout << ans << endl;
}
