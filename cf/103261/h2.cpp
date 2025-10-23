#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;

	int n, m; cin >> n >> m;
	vector<vector<int>> grid(n, vector<int>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> grid[i][j];
		}
	}


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

		const int INF = 1e9;
		const int S = (500 * 50 + 1);
		const int M = 2*S;
		vector dp(M, -INF);
		dp[S] = 0;

		for (int i = 0; i < n; i++) {
			auto &cur = testa[i];
			int mx = 0;
			for(auto x : dp) mx = max(mx, x);
			vector ndp(M, mx);
			for (int s = 0; s < M; s++) if (dp[s] >= 0) {
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

		ans += dp[S];

		vector ngrid(m, vector<int>(n));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				ngrid[j][i] = grid[i][j];
		swap(grid, ngrid);
		swap(n, m);
	}

	cout << ans << endl;
}

