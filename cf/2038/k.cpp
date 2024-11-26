#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define int long long
using namespace std;

int32_t main(){_
	int n, a, b; cin >> n >> a >> b;
	int x = n, y = n;
	while (gcd(x, a) != 1) x--;
	while (gcd(y, b) != 1) y--;
	int ans = 0;
	for (int i = 1; i <= x; ++i) ans += 1 + gcd(i, a);
	for (int j = 2; j <= y; ++j) ans += 1 + gcd(j, b);
	vector<vector<int>> dp(2, vector<int>(n-y+2, 1e18));
	vector<int> pc(n+1), pr(n+1);
	for (int i = 1; i <= n; ++i) pc[i] = gcd(i, b), pr[i] = gcd(i, a);
	dp[x&1][1] = 0;
	for (int i = x; i <= n; ++i) {
		for (int j = y; j <= n; ++j) {
			if (i == x and j == y) continue;
			int t = i&1;
			dp[t][j-y+1] = min(dp[t][j-y], dp[t^1][j-y+1]) + pr[i] + pc[j];
		}
	}
	cout << ans + dp[n&1][n-y+1] << endl;
}

