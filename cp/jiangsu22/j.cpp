#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
//#define int unsigned ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

map<int, int> solve;
using ull = unsigned long long;

const int BIG = 64;
vector dp(BIG + 2, vector(2, 0));
vector<ull> pots(BIG + 2, 0);
vector<int> v(BIG);

inline int g(ull n) {
	int m = 0;
	for (; n; n /= 2) {
		int cnt = 0;
		while (n % 2 == 0) {
			cnt++;
			n /= 2;
		}
		v[m++] = cnt;
	}

	dp[m][0] = dp[m][1] = 0;
	for (int i = m - 1; i >= 0; --i) {
		for (int j : {0, 1}) {
			int k = v[i] + j;
			dp[i][j] = min<ull>(2*dp[i + 1][0] + k + pots[k] * dp[i + 1][1], BIG);
		}
	}

	return dp[0][0];
}

int32_t main() {
	fast_io;
	int t; cin >> t;

	for (int i = 0; i < BIG; i++) {
		pots[i] = (ull(1) << i) - 1;
	}

	while (t--) {
		ull n; cin >> n;
		
		int ans = g(n);
		if (ans >= BIG) cout << 0 << endl;
		else {
			cout << (ull(1) << ans) << endl;
		}
	}
	return 0;
}

