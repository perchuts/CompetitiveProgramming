#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

const int maxn = 5e6 + 10;

int dp[maxn], lg[maxn];

mt19937 rng(time(0));

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}
int32_t main() {_
	for (int i = 1; i < maxn; ++i) {
		dp[i] = dp[i-1] + 1;
		for (int j = 2; j <= min(i, 13LL); ++j) {
			if (i % j == 0) dp[i] = min(dp[i], dp[i/j] + j + 2);
		}
	}
	for (int i = 2; i < maxn; ++i) lg[i] = 1 + lg[i/3];
	int n; cin >> n;
	//int n = rnd(1e10, 1e12);
	//cout << "n = " << n << endl;
	if (n < maxn) {
		cout << dp[n] << endl;
		exit(0);
	}
	int ans = 1000;
	unordered_map<int, int> mp;
	auto rec = [&] (auto&& self, int k, int cost) -> void {
		if (mp.count(k) and mp[k] <= cost) return;
		mp[k] = cost;
		if (k < maxn) {
			ans = min(ans, dp[k] + cost);
			return;
		}
		for (int j = 2; j < 40; ++j) {
			self(self, k / j, cost + j + 2 + (k % j));
		}
	};
	rec(rec, n, 0);
	cout << ans << endl;
}
