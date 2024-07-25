#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define sz(x) (int) x.size()
#define all(x) begin(x), end(x)
#define pb push_back

using namespace std;

using ll = long long;
using ii = pair<int, int>;

int dp[105][105][105][105];
ii t[105][105][105];

int32_t main() {_
	int n; cin >> n;
	vector<int> a(n), b(n);
	for (auto& x : a) cin >> x;
	for (auto& x : b) cin >> x;
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= i; ++j) {
			for (int k = 1; k < i; ++k) {
				if (a[k-1] != b[j-1]) continue;
				for (int w = k + 1; w <= i; ++w) {
					if (dp[i][j-1][w]) {
						t[i][j][k] = {i, w};
						dp[i][j][k] = 1;
					}
				}
			}
			if (a[i-1] != b[j-1]) continue;
			if (j == 1) {
				t[i][1][i] = {0, 0};
				dp[i][1][i] = 1;
			}
			for (int i2 = i-1; i2 >= 1; --i2) {
				for (int k2 = 1; k2 <= i2; ++k2) {
					if (dp[i2][j-1][k2]) {
						t[i][j][i] = {i2, k2};
						dp[i][j][i] = 1;
					}
				}
			}
		}
	}
	vector<int> p(n+1);
	int st = -1;
	for (int i = 1; i <= n; ++i) if (dp[n][n][i]) st = i;
	if (st == -1) {
		cout << "NO" << endl;
		return 0;
	}
	cout << "YES" << endl;
	ii cur = {n, st};
	for (int j = n; j >= 1; --j) {
		p[cur.second] = j;
		cout << j << ' ' << cur.first << ' ' << cur.second << endl;
		cur = t[cur.first][j][cur.second];
	}
	for (int i = 1; i <= n; ++i) cout << p[i] << ' ';
	cout << endl;
	string ans;
	stack<int> stk;
	int ptr = 1;
	for (int j = 1; j <= n; ++j) {
		while (ptr <= n && (stk.empty() || stk.top() != j)) ans += 'S', stk.push(p[ptr++]);
		assert(stk.top() == j);
		ans += 'C';
		stk.pop();
	}
	cout << ans << endl;

}
