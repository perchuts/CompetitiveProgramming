#include <bits/stdc++.h>
#define GATO
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int solve(int n, int m, vector<vector<int>> grid) {
	int ans = 0;
	for (int _ = 0; _ < 2; _++) {
		vector<vector<int>> testa(n);
		for (int i = 0; i < n; i++) {
			int prv = (i + n - 1) % n;
			auto &cur = testa[i];
			for (int j = 0; j < m; j++) cur.push_back(grid[prv][j] - grid[i][j]);
			// 0:-----------
			//   -----------
			//   -----------
			//   -----------
			//   val = dx
			//   ***********
			//   dx
			// 0:-----------
			sort(cur.begin(), cur.end());
			//cur.erase(unique(cur.begin(), cur.end()), cur.end());
		}

		if (n == 2) {
			int best = 0;
			auto& cur = testa[0];
			for (int l = 0, r = 0; l < cur.size(); l = r) {
				while (r < cur.size() && cur[l] == cur[r]) r++;

				int val = cur[l];
				int qt = r - l;
				
				best = max(best, qt);
			}
			ans += 2*best;
		} else {
			const int INF = 1e9;
			const int S = (500 * 50 + 1);
			const int M = 2*S;
			vector dp(M, -INF);
			dp[S] = 0;

			for (int i = 1; i < n - 1; i++) {
				auto &cur = testa[i];
				vector ndp(M, -INF);
				int mx = 0;
				for (auto x : dp) mx = max(mx, x);
				for (int s = 0; s < M; s++) if (dp[s] >= 0) {
					ndp[s] = max(ndp[s], mx);
					for (int l = 0, r = 0; l < cur.size(); l = r) {
						while (r < cur.size() && cur[l] == cur[r]) r++;

						int val = cur[l];
						int qt = r - l;

						if (0 <= s + val && s + val < M)
							ndp[s + val] = max(ndp[s + val], dp[s] + qt);
					}
				}
				swap(ndp, dp);
			}

			int best = 0;
			for (int s = 0; s < M; s++) {
				auto &cur = testa[n - 1];
				for (int l = 0, r = 0; l < cur.size(); l = r) {
					while (r < cur.size() && cur[l] == cur[r]) r++;
					int val = cur[l];
					int qt = r - l;

					int delta = (s + val) - S;
					for (int j = 0; j < m; j++) {
						if (grid[n - 1][j] + delta == grid[0][j]) qt++;
					}
					best = max(best, dp[s] + qt);
				}
			}
			ans += best;
		}

		vector ngrid(m, vector<int>(n));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				ngrid[j][i] = grid[i][j];
		swap(grid, ngrid);
		swap(n, m);
	}

	return ans;
}

int brute(int n, int m, vector<vector<int>> grid) {
	int ans = 0;
	for (int _ = 0; _ < 2; _++) {
		vector<vector<int>> testa(n);
		for (int i = 0; i < n; i++) {
			int prv = (i + n - 1) % n;
			auto &cur = testa[i];
			for (int j = 0; j < m; j++) cur.push_back(grid[prv][j] - grid[i][j]);
			// 0:-----------
			//   -----------
			//   -----------
			//   -----------
			//   val = dx
			//   ***********
			//   dx
			// 0:-----------
			sort(cur.begin(), cur.end());
			//cur.erase(unique(cur.begin(), cur.end()), cur.end());
		}

		ans += best;

		vector ngrid(m, vector<int>(n));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				ngrid[j][i] = grid[i][j];
		swap(grid, ngrid);
		swap(n, m);
	}

	return ans;
}

int32_t main() {
#ifndef GATO
	fast_io;

	int n, m; cin >> n >> m;
	vector<vector<int>> grid(n, vector<int>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> grid[i][j];
		}
	}

	int ans = solve(n, m, grid);
#else
	
	srand(2);
	int t = 0;
	while (true) {

		int n = rand() % 3 + 2;
		int m = rand() % 3 + 2;
		vector<vector<int>> grid(n, vector<int>(m));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				grid[i][j] = rand() % 5;

		cout << "AC " << t++;
	}

#endif

}
