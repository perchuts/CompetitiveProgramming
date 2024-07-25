#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define sz(x) (int) x.size()
#define all(x) begin(x), end(x)
#define pb push_back
#define int long long

using namespace std;

using ll = long long;

int32_t main() {_
	string s, t; cin >> s >> t;
	int n = sz(s), m = sz(t);
	vector<vector<int>> dp(n + 1, vector<int>(m + 1));
	dp[0][0] = 1;
	vector<int> ok(260);
	ok['a'] = ok['e'] = ok['i'] = ok['o'] = ok['u'] = ok['y'] = 1;
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= m; ++j) {
			if (i == j && j == 0) continue;
			if (i == 0) {
				char b = tolower(t[j-1]);
				if (ok[b]) dp[i][j] = dp[i][j-1];
				continue;
			}
			if (j == 0) continue;
			char a = tolower(s[i-1]), b = tolower(t[j-1]);
			if (a == b) dp[i][j] = dp[i-1][j-1];
			if (ok[b]) dp[i][j] |= dp[i][j-1];	
		}
	}
	cout << (dp[n][m] ? "Same" : "Different") << endl;
}
