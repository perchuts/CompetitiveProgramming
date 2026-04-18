#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;

int solve(int n, int m, int a) {
	if (n == 0) return n+m-1;
	int b = n+m-1-a;
	int ans = 0;
	for (int delta = -1; delta <= 1; ++delta) {
		int C = b - n - m + 2 - delta;
		int lim = min(n-1, m-1+delta);
		if (lim < 0) continue;
		if (C >= 0) {
			if (delta == 1) {
				if (lim == 0) continue;
				else ans = max(ans, m + 1 - (C + 2));
			} else {
				ans = max(ans, m - C);
			}
		}
		else {
			if (delta == 1) {
				int opt;
				if (lim == 0) continue;
				else if (C == -1) {
					opt = 1;
				} else {
					opt = min(lim, (-C)/2);
				}
				ans = max(ans, m + opt - max(0LL, C + 2*opt));
			} else {
				int opt = min(lim, (-C)/2);
				ans = max(ans, m + opt - max(0LL, C + 2*opt));
			}
		}
	}
	return ans;
}

int32_t main() {_
	int t; cin >> t;
	while (t--) {
		int n, m, a; cin >> n >> m >> a;
		cout << solve(n, m, a) << endl;
	}
}
