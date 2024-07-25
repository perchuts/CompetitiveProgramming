#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define sz(x) (int) x.size()
#define all(x) begin(x), end(x)
#define pb push_back

using namespace std;

using ll = long long;
using ii = pair<int, int>;
using iii = tuple<int, int, int>;

int dp[105][105][105][105];
int quem[105][105][105][105];
iii t[105][105][105][105];

int32_t main() {_
	int n; cin >> n;
	vector<int> a(n), b(n);
	for (auto& x : a) cin >> x;
	for (auto& x : b) cin >> x;

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= i; ++j) {
			for (int k = 1; k < i; ++k) {
				if (a[k-1] != b[j-1]) continue;
				for (int l = 0; l < k; ++l) {
					if (dp[i][j-1][k+1][l]) dp[i][j][k][l] = 1, t[i][j][k][l] = {i, quem[i][j-1][k+1][l], l};
					if (k == l && dp[i][j-1][k+1][k]) dp[i][j][k][l] = 1, t[i][j][k][l] = {i, quem[i][j-1][k+1][k], k};
				}
			}
			if (a[i-1] == b[j-1]) {
				// se i-1 era o ultimo, o L pode ser qualquer coisa
				for (int l = 0; l < i; ++l) {
					if (dp[i-1][j-1][l+1][l]) dp[i][j][i][l] = 1, t[i][j][i][l] = {i-1, quem[i-1][j-1][l+1][l], l};
				}
				// se eu passei ANTES do i-1, entao o L vai ser o i-1
				for (int i2 = 0; i2 <= i-2; ++i2) {
					for (int l2 = 0; l2 < i2; ++l2) {
						if (dp[i2][j-1][l2+1][l2]) dp[i][j][i][i-1] = 1, t[i][j][i][i-1] = {i2, quem[i2][j-1][l2+1][l2], l2};
					}
				}
			}
			if (j == 1) dp[i][j][i][i-1] = 1;
			for (int l = 0; l < i; ++l) {
				for (int k = i; k > l; --k) {
					if (dp[i][j][k][l]) quem[i][j][k][l] = k;
					else dp[i][j][k][l] = dp[i][j][k+1][l], quem[i][j][k][l] = quem[i][j][k+1][l];
				}
			}
		}
	}
	vector<int> p(n+1);
	int st = -1;
	for (int i = 1; i <= n; ++i) if (dp[n][n][i][0]) st = i;
	if (st == -1) {
		cout << "NO" << endl;
		return 0;
	}
	cout << "YES" << endl;
	iii cur = {n, st, 0};
	for (int j = n; j >= 1; --j) {
		auto [cur_i, cur_k, cur_l] = cur;
		cout << cur_i << ' ' << j << ' ' << cur_k << ' ' << cur_l << endl;
		p[cur_k] = j;
		cur = t[cur_i][j][cur_k][cur_l];
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
