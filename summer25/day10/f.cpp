#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

const int LINF = 1e18;

int32_t main() {
	fast_io;
	int n, K; cin >> n >> K;
	vector<int> a(n);
	for (auto& x : a) cin >> x;
	vector<int> pref(n);
	for (int i = 0; i < n; ++i) pref[i] = (i == 0 ? 0 : pref[i-1]) + a[i];
	auto query = [&] (int l, int r) {
		int x = (l == 0 ? 0 : -pref[l-1]) + pref[r];
		return x*(r-l+1);
	};
	vector<vector<int>> dp(n+1, vector<int>(2));
	auto solve = [&] (auto&& self, int k, int l, int r, int lk, int rk) -> void{
		if (l > r) return;
		int m = (l+r)/2, p = -1;
		auto& ans = dp[m][k&1] = LINF;
		for (int i = max(m, lk); i <= rk; ++i) {
			int at = dp[i+1][~k&1] + query(m, i);
			if (at < ans) ans = at, p = i;
		}
		self(self, k, l, m-1, lk, p), self(self, k, m+1, r, p, rk);
	};
	++K;
	dp[n][0] = dp[n][1] = 0;
	for (int i = 0; i < n; ++i) dp[i][0] = LINF;
	for (int i = 1; i <= K; ++i) solve(solve, i, 0, n-i, 0, n-i);
	cout << dp[0][K&1] << endl;
}
