#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
// Auto explicativo
#pragma GCC optimize("unroll-loops")
// Vetorizacao
#pragma GCC target("avx2")
// Para operacoes com bits
#pragma GCC target("bmi,bmi2,popcnt,lzcnt")
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

vector<int> brute(int n, vector<int> h) {
	vector<int> score(n);
	int tot = 0;
	for (int i = 1; i < n; ++i) score[i] = abs(h[i] - h[i-1]), tot += score[i];
	vector<int> ans(n, tot);
	for (int i = 0; i < n-1; ++i) {
		for (int j = i+1; j < n; ++j) {
			int cur = tot - score[i] - score[i+1] - (j == i+1 ? 0 : score[j]) - (j == n-1 ? 0 : score[j+1]);	
			cur += (i == 0 ? 0 : abs(h[i-1] - h[j]));
			cur += (j == n-1 ? 0 : abs(h[i] - h[j+1]));
			if (j == i+1) cur += abs(h[i] - h[j]);
			else cur += abs(h[i+1] - h[j]) + abs(h[j-1] - h[i]);
			ans[i] = min(ans[i], cur);
			ans[j] = min(ans[j], cur);
		}
	}
	return ans;
}

int32_t main() {
	fast_io;
	int n; cin >> n;
	vector<int> h(n);
	for (auto& x : h) cin >> x;
	vector<int> score(n);
	int tot = 0;
	for (int i = 1; i < n; ++i) score[i] = abs(h[i] - h[i-1]), tot += score[i];
	vector<int> ans(n, tot);
	for (int i = 0; i < n; ++i) {
		sweep.emplace_back(h[i], i, 0);
		int big = max((i==n-1?0:h[i+1]), (i==0?0:h[i-1]));
		if (i != n-1) sweep.emplace_back(big, i, 1);
	}
	sort(begin(sweep), end(sweep));
	vector<int> ans(n);

	for (auto [val, id, type] : sweep) {
		// to fixando que o proximo cara eh maior que eu
		if (type) {
			
		} else {

		}
	}
}
