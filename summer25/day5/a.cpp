#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;

	int n;
	cin >> n;

	vector<int> b(n), c(n);
	for (auto &i : b) cin >> i;
	for (auto &i : c) cin >> i;

	int k; cin >> k;
	const int inf = 1e18;
	vector dp(k + 1, inf);
	dp[0] = 0;

	for (int i = 0; i < n; i++) {
		vector<int> decomp;
		int val = c[i];
		while (val > 0) {
			decomp.push_back((val+1)/2);
			val -= (val+1)/2;
		}

		for (int w : decomp) {
			int x = b[i] * w;

			for (int j = k - x; j >= 0; --j) if (dp[j] != inf) {
				dp[j + x] = min(dp[j + x], dp[j] + w);
			}
			//cout << "x=" << x << " w=" << w << endl;
			//for (int j = 0; j <= k; j++)
			//	cout << dp[j] << " ";
			//cout << endl;
		}
	}

	cout << dp[k] << endl;
}
