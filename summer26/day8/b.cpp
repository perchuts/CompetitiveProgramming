#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll

using namespace std;

using ll = long long;

int32_t main() {_
	int n, L; cin >> n >> L;
	vector<vector<int>> c(n, vector<int>(n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> c[i][j];
		}
	}
	if (n < 12) {
		vector<int> p(n-1); iota(begin(p), end(p), 1);
		do {
			int tot = c[0][p[0]] + c[p[n-2]][0];
			for (int i = 1; i < n-1; ++i) tot += c[p[i-1]][p[i]];
			if (tot == L) {
				cout << "possible" << endl;
				exit(0);
			}
		} while (next_permutation(begin(p), end(p)));
		cout << "impossible" << endl;
		exit(0);
	}
	// dp[mascara][final] = vector
	vector<vector<int>> dp(1<<n);
	int tam_esq = (n-2)/2, tam_dir = (n-1)/2;
	vector<int> cpl(1<<n);
	for (int x = 1; x < n; ++x) {
		// bit 0 sempre desligado!
		for (int j = 0; j < (1 << n); j += 2) {
			int cnt = __builtin_popcount(j);
			if ((j >> x & 1)) continue;
			if (cnt != tam_esq and cnt != tam_dir) continue;
			vector<int> bichos;
			cpl[j] = 0;
			for (int i = 1; i < n; ++i) {
				if (i == x) continue;	
				if (j >> i & 1) bichos.pb(i);
				else cpl[j] += (1 << i);
			}
			dp[j].clear();
			int t = bichos.size();
			do {
				int cost = c[0][bichos[0]] + c[bichos[t-1]][x];
				for (int i = 1; i < t; ++i) cost += c[bichos[i-1]][bichos[i]];
				dp[j].push_back(cost);
			} while (next_permutation(begin(bichos), end(bichos)));

			sort(begin(dp[j]), end(dp[j]));
		}
		for (int j = 0; j < (1 << n); j += 2) {
			int cnt = __builtin_popcount(j);
			if (cnt != tam_esq and cnt != tam_dir) continue;
			if ((j >> x & 1)) continue;
			int z = cpl[j];
			for (auto k : dp[j]) {
				if (k > L) break;
				int want = lower_bound(begin(dp[z]), end(dp[z]), L - k) - begin(dp[z]);
				if (want < dp[z].size() and dp[z][want] + k == L) { 
					cout << "possible" << endl;
					exit(0);
				}
			}
		}
	}
	cout << "impossible" << endl;
}
