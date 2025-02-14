#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

bool test(vector<vector<int>>& grid, int x, int need) {
	int n = grid.size();
	int m = grid[0].size();
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int l = 0, r = 0; l < m; l = r) {
			while (r < m && grid[i][l] == grid[i][r]) r++;
			if (grid[i][l]) continue;
			cnt += (r - l) / x;
			if (cnt >= need) return true;
		}
	}
	return false;
}

bool test2(vector<vector<int>>& grid, int x) {
	int n = grid.size();
	int m = grid[0].size();

	vector dp(m, 0), mx(m, 0);
	for (int i = 0; i < n; i++) {
		vector ndp(m, 0);

		int cnt = 0;
		for (int j = 0; j < m; j++)
			cnt += mx[j] >= x;

		for (int l = 0, r = 0; l < m; l = r) {
			while (r < m && grid[i][l] == grid[i][r]) r++;
			if (grid[i][l]) continue;
			if (cnt && (r - l) >= x) return true;
		}

		for (int j = 0; j < m; j++) {
			if (grid[i][j]) continue;
			ndp[j] = dp[j] + 1;
			mx[j] = max(mx[j], ndp[j]);
		}
		dp = ndp;
	}
	return false;
}

bool inter(int l1, int r1, int i1, int l2, int r2, int i2) {
	return l1 <= i2 && i2 <= r1 && l2 <= i1 && i1 <= r2;
}

bool test3(vector<vector<int>>& grid, int x) {
	int k = x;
	int n = grid.size();
	int m = grid[0].size();

	int l1 = -1, r1 = -1, i1 = -1;
	int l2 = -1, r2 = -1, i2 = -1;

	for (int i = 0; i < n; i++) {
		for (int l = 0, r = 0; l < m; l = r) {
			while (r < m && grid[i][l] == grid[i][r]) r++;
			if (grid[i][l]) continue;
			if ((r - l) >= x) {
				l1 = l, r1 = r - 1, i1 = i;
			}
		}
	}

	for (int j = 0; j < m; j++) {
		for (int l = 0, r = 0; l < n; l = r) {
			while (r < n && grid[l][j] == grid[r][j]) r++;
			if (grid[l][j]) continue;
			if ((r - l) >= x) {
				l2 = l, r2 = r - 1, i2 = j;
			}
		}
	}

	if (l1 == -1 || l2 == -1) return false;
	
	if (!inter(l1, l1 + k - 1, i1, l2, l2 + k - 1, i2)) return true;
	if (!inter(r1 - k + 1, r1, i1, l2, l2 + k - 1, i2)) return true;
	if (!inter(l1, l1 + k - 1, i1, r2 - k + 1, r2, i2)) return true;
	if (!inter(r1 - k + 1, r1, i1, r2 - k + 1, r2, i2)) return true;

	return false;
}

int32_t main() {
	fast_io;

	int n, m;
	int k;
	cin >> n >> k;
	m = n;

	vector<vector<int>> grid(n, vector<int>(m));
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		for (int j = 0; j < m; j++) {
			grid[i][j] = s[j] == 'X' ? 1 : 0;
		}
	}
	vector trans(m, vector(n, 0ll));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			trans[j][i] = grid[i][j];

	auto r_grid = grid;
	auto r_trans = trans;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			r_grid[n - i - 1][j] = grid[i][j];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			r_trans[m - j - 1][i] = trans[j][i];
	}

	auto check = [&] (int x) {
		if (test(grid, x, k)) return true;
		if (test(trans, x, k)) return true;
		if (test3(grid, x)) return true;
		//if (test2(grid, x)) return true;
		//if (test2(r_grid, x)) return true;
		//if (test2(trans, x)) return true;
		//if (test2(r_trans, x)) return true;
		return false;
	};

	int lo = 0, hi = max(n, m) + 1; 
	while (lo < hi) {
		int mid = (lo + hi + 1) / 2;

		if (mid == 0 || check(mid))
			lo = mid;
		else
			hi = mid - 1;
	}

	cout << lo << endl;
}
