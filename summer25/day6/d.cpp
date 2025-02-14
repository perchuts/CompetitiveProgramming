#include <bits/stdc++.h>
using namespace std;

#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;
	int n, q; cin >> n >> q;
	vector<pair<int, int>> v(q);
	int inf = 100000000;
	vector dp(n, vector(n, inf));
	dp[n/2][n/2] = 0;
	int y_last = n/2;
	for (auto [x_p, y_p] : v) {
		cin >> x_p >> y_p;
		vector ndp(n, vector(n, inf));
		array<int, 3> pos;
		for (int onde_parou = 0; onde_parou < 3; ++onde_parou) {
			for (int outro = 0; outro < n and outro + y_last <= 3*(n/2); ++outro) {
				pos[onde_parou] = y_last;
				if (onde_parou == 0) pos[1] = outro;
				else pos[0] = outro;
				if (onde_parou == 2) pos[1] = 3*(n/2) - outro - y_last;
				else pos[2] = 3*(n/2) - outro - y_last;
				// temos as posicoes dos 3 bichos. vamos brutar como vamos fazer a primeira parte, e depois como fazer a segunda
				// quem = quem vai me levar
				int p0 = pos[0], p1 = pos[1], p2 = pos[2];
				if (max({p0, p1, p2}) >= n) continue;
				for (int quem = 0; quem < 3; ++quem) {
					//if (y_p == 0 and onde_parou  == 0 and outro == 3) cout << pos[0] << ' ' << pos[1] << ' ' << pos[2] << endl;
					for (int op1 = 0; op1 < 3; ++op1) {
						if (op1 == quem) continue;
						for (int op2 = 0; op2 < 3; ++op2) {
							if (op2 == quem) continue;
							pos[0] = p0, pos[1] = p1, pos[2] = p2;
							int d1 = x_p - pos[quem], d2 = y_p - x_p;
							if (pos[op1] - d1 < 0 or n <= pos[op1] - d1) continue;
							pos[op1] -= d1;
							if (pos[op2] - d2 < 0 or n <= pos[op2] - d2) continue;
							pos[op2] -= d2;
							pos[quem] = y_p;
							ndp[pos[0]][pos[1]] = min(ndp[pos[0]][pos[1]], dp[p0][p1] + abs(d1)+abs(d2));
						}
					}
				}
			}
		}
		y_last = y_p;
		swap(dp, ndp);
	}
	int best = inf;
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) best = min(best, dp[i][j]);
	cout << best << endl;

}
