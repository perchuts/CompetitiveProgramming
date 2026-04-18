#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

int solve(int n, vector<int> p) {
	vector<vector<int>> g(n);
	for (int i = 1; i < n; ++i) g[p[i]].pb(i);
	vector<int> eh_folha(n);
	for (int i = 1; i < n; ++i) if (g[i].size() == 0) eh_folha[i] = 1;
	int l = 0, r = n, ans = 0;
	vector<int> tipo(n);
	auto possible = [&] (int x) {
		auto dfs = [&] (auto&& self, int u) -> void {
			if (eh_folha[u]) {
				if (u <= x) tipo[u] = 1;
				else tipo[u] = -1;
				return;
			}
			int A = 0, B = 0, C = 0;
			for (auto v : g[u]) {
				self(self, v);
				if (tipo[v] == 0) ++C;
				if (tipo[v] == -1) ++B;
				if (tipo[v] == 1) ++A;
			}
			if (A == B) tipo[u] = 0;
			else if (A > B) tipo[u] = 1;
			else tipo[u] = -1;
		};
		dfs(dfs, 0);
		return tipo[0] >= 0;
	};
	while (l <= r) {
		int md = l + (r-l+1)/2;
		if (possible(md)) ans = md, r = md-1;
		else l = md+1;
	}
	return ans+1;
}

int brute(int n, vector<int> p) {
	vector<vector<int>> g(n);
	for (int i = 1; i < n; ++i) g[i].pb(p[i]), g[p[i]].pb(i);
	vector<vector<int>> dp(1<<n, vector<int>(2));
	vector<int> eh_folha(n);
	for (int i = 1; i < n; ++i) eh_folha[i] = g[i].size() == 1;
	vector<int> subt(n);
	auto dfs = [&] (auto&& self, int u) -> void {
		subt[u] = (1 << u);
		for (auto v : g[u]) {
			if (v == p[u]) continue;
			self(self, v);
			subt[u] |= subt[v];
		}
	};
	dfs(dfs, 0);
	for (int i = 1; i < (1<<n); ++i) {
		bool ok = 1;
		int f1 = -1, f2 = -1, folhas = 0;
		for (int j = 0; j < n; ++j) {
			if (i >> j & 1) {
				ok &= (i >> p[j] & 1);
				if (eh_folha[j]) {
					if (f1 == -1) f1 = j;
					else f2 = j;
					folhas |= (1 << j);
				}
			}
		}
		if (!ok) continue;
		if (folhas == 0) continue;
		if (f2 == -1) {
			assert(f1 != -1);
			dp[i][0] = dp[i][1] = f1;
			continue;
		} 
		dp[i][0] = n, dp[i][1] = 0;
		for (int j = 1; j < n; ++j) {
			if (i >> j & 1) {
				int minha_subt = subt[j] & i;
				if ((minha_subt & folhas) == folhas) continue;
				dp[i][0] = min(dp[i][0], dp[i - minha_subt][1]);
				dp[i][1] = max(dp[i][0], dp[i - minha_subt][0]);
			}
		}
	}
	return dp.back().back()+1;
}

int32_t main() {_
	

#ifndef gato
	int n; cin >> n;
	vector<int> p(n);
	for (int i = 1; i < n; ++i) cin >> p[i], --p[i];
	cout << solve(n, p) << endl;
	//cout << brute(n, p) << endl;
#else
#endif
}
