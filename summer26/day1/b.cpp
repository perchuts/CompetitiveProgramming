#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back

using ll = long long;
using namespace std;

const int maxn = 2e5+10;

const int INF = 1e18;

int calc(vector<int> &vals, vector<vector<int>> &costs){
	int m = vals.size();
	int v = -INF;
	for (int f = 0; f < 2; ++f){
		vector<vector<int>> dp(m+1, vector<int>(2, -INF));
		dp[0][f] = 0;

		for (int i = 1; i <= m; ++i){
			int cur = vals[i-1];
			for (int a = 0; a < 2; ++a)
				for (int b = 0; b < 2; ++b){
					if (i == m and b != f) continue;
					int ad = costs[cur][a + (!b)];
					dp[i][b] = max(dp[i][b], dp[i-1][a]+ad); 
				}
		}

		v = max(v, dp[m][f]);
	}
	return v;
}


int solve(int n, vector<int> ps, vector<int> qs, vector<vector<int>> &costs) {
	vector<int> loc(n);
	for (int i = 0; i < n; ++i) loc[ps[i]] = i;

	vector<bool> vis(n);
	int ans = 0;
	for (int i = 0; i < n; ++i) if (!vis[i]){
		if (ps[i] == qs[i]){
			ans = (ans + costs[qs[i]][1]);
			continue;
		}	

		vector<int> cyc;
		cyc.pb(ps[i]);
		int x = i;
		while (!vis[x]){
			vis[x] = true;
			cyc.pb(qs[x]);
			x = loc[qs[x]];
		}
		if (cyc[0] == cyc.back()) cyc.pop_back();
		ans = (ans + calc(cyc, costs));
	}
	return ans;
}
mt19937 rng(time(0));
int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

int brute(int n, vector<int> p, vector<int> q, vector<vector<int>> costs) {
	int ans = -1e18;
	for (int i = 0; i < (1 << n); ++i) {
		vector<int> z(n);
		for (int j = 0; j < n; ++j) {
			if (i >> j & 1) {
				z[j] = p[j];
			} else {
				z[j] = q[j];
			}
		}
		vector<int> cnt(n);
		for (auto x : z) cnt[x]++;
		int cur = 0;
		for (int j = 0; j < n; ++j) assert(cnt[j] <= 2), cur += costs[j][cnt[j]];
		ans = max(ans, cur);
	}
	return ans;
}

int32_t main() {_
#ifndef gato
	int t; cin >> t;
	while (t--) {

		int n; cin >> n;
		vector<int> ps(n), qs(n);
		vector<vector<int>> costs(n, vector<int>(3));
		for (int i = 0; i < n; ++i) cin >> ps[i];
		for (int i = 0; i < n; ++i) cin >> qs[i];
		for (auto &v : ps) v--;
		for (auto &v : qs) v--;

		for (int i = 0; i < 3; ++i){
			for (int a = 0; a < n; ++a){
				cin >> costs[a][i];
			}
		}
		cout << solve(n, ps, qs, costs) << endl;
	}
#else
	int t = 1;
	while (true) {
		int n = rnd(1, 6);
		vector<int> p(n), q(n);
		iota(begin(p), end(p), 0);
		q = p;
		shuffle(begin(p), end(p), rng);
		shuffle(begin(q), end(q), rng);
		vector<vector<int>> costs(n, vector<int>(3));
		for (auto& x : costs) {
			for (auto& y : x) y = rnd(-100, 100);
		}
		auto my = solve(n, p, q, costs);
		auto ans = brute(n, p, q, costs);
		if (my != ans) {
			cout << n << endl;
			for (auto x : p) cout << x + 1 << " ";
			cout << endl;
			for (auto x : q) cout << x + 1 << " ";
			cout << endl;
			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < n; ++j) {
					cout << costs[j][i] << " ";
				}
				cout << endl;
			}
			cout << "solve: " << my << endl;
			cout << "brute: " << ans << endl;
			exit(0);
		}
		cout << "AC " << t++ << endl;
	}
#endif
}
