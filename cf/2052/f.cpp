#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

void test_case() {
	int n; cin >> n;
	array<string, 2> s;
	cin >> s[0] >> s[1];

	vector dp(4, 0);
	dp[0] = 1;
	auto op = [&] (int a, int b) {
		a += b;
		if (a >= 2) a = 2;
		return a;
	};

	for (int i = 0; i < n; i++) {
		vector ndp(4, 0);
		for (int mask = 0; mask < 4; mask++) {
			for (int nmask = 0; nmask < 4; nmask++) {
				if ((nmask&1) && (mask&1)) continue;
				if ((nmask&2) && (mask&2)) continue;
				if (s[0][i] == '#' && (mask&1)) continue;
				if (s[1][i] == '#' && (mask&2)) continue;
				if (s[0][i] == '#' && (nmask&1)) continue;
				if (s[1][i] == '#' && (nmask&2)) continue;

				bool ok = true;
				if (s[0][i] == '.') ok &= (mask&1) || (nmask&1) || (mask == 0 && nmask == 0 && s[1][i] == '.');
				if (s[1][i] == '.') ok &= (mask&2) || (nmask&2) || (mask == 0 && nmask == 0 && s[0][i] == '.');
				if (ok) ndp[nmask] = op(ndp[nmask], dp[mask]);
			}
		}

		swap(dp, ndp);
	}

	cout << (dp[0] == 0 ? "None" : (dp[0] == 1 ? "Unique" : "Multiple")) << endl;
}

int32_t main() {
	fast_io;

	int t; cin >> t;
	while (t--) test_case();
}
