#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
//#define endl '\n'
typedef long long ll;

vector<int> query(string s) {
	cout << "QUERY " << s << endl;
	vector<int> ans(s.size());
	for (auto& x : ans) cin >> x;
	return ans;
}

void answer(vector<pair<int, int>> ans) {
	cout << "ANSWER" << endl;
	for (auto [x, y] : ans) cout << x << ' ' << y << endl;
}
int32_t main() {
	fast_io;
	int n; cin >> n;
	vector<int> deg = query(string(n, '1')); 
	vector<vector<int>> qt;
	for (int i = 0; (1 << i) <= n; ++i) {
		string s(n, '0');
		for (int j = 1; j <= n; ++j) {
			if (j >> i & 1) s[j-1] = '1'; 
		}
		qt.push_back(query(s));
	}
	vector<pair<int, int>> ans;
	queue<int> q;
	vector<int> foi(n);
	for (int i = 0; i < n; ++i) if (deg[i] == 1) q.push(i+1), foi[i] = 1;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (deg[u-1] == 0) continue;
		int other = 0;
		for (int j = 0; (1 << j) <= n; ++j) if (qt[j][u-1]) {
			other += (1 << j);
		}
		// 1 indexado
		for (int j = 0; (1 << j) <= n; ++j) {
			if (u >> j & 1) qt[j][other-1]--;
		}
		deg[other-1]--;
		if (deg[other-1] == 1 and foi[other-1] == 0) foi[other-1] = 1, q.push(other);
		ans.push_back({u, other});
	}
	assert(ans.size() == n-1);
	answer(ans);
}
