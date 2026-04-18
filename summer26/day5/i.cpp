#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back
using namespace std;

using ll = long long;

const int mod = (119<<23)+1;

int32_t main() {_
	string s; cin >> s;
	int n = s.size();
	vector dp(2, vector(2, 0LL));
	dp[1][1] = 1;
	for (int i = 1; i < n; ++i) {
		vector ndp(2, vector(2, 0LL));
		ndp[0][1] = (dp[1][0] + dp[1][1]) % mod;
		ndp[1][1] = (dp[0][0] + dp[0][1]) % mod;
		if (s[i-1] == '0') {
			ndp[0][0] = dp[0][0];
			ndp[1][0] = dp[1][0];
		} else {
			ndp[0][0] = (dp[0][0] + dp[0][1]) % mod;
			ndp[1][0] = (dp[1][0] + dp[1][1]) % mod;
		}
		swap(dp, ndp);
	}
	cout << (dp[0][0] + dp[0][1]) % mod << endl;
}
