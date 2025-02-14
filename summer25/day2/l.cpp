#include <bits/stdc++.h>
using namespace std;

#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

ll pot = 100001;
inline ll hsh (int x, int y, int z) {
	assert(max({x, y, z}) < pot);
	ll h = x + pot * y + pot*pot*z; 
	return h;
}

int32_t main() {
	fast_io;
	vector<int> cap(3);
	for (auto& x : cap) cin >> x;
	int a, b, c; cin >> a >> b >> c;
	map<ll, int> dist;
	vector<int> ans(max({cap[0], cap[1], cap[2]}) + 1, pot*6969);
	queue<array<int, 4>> q;
	q.push({a, b, c, 0});
	dist[hsh(a, b, c)] = 0;
	while (!q.empty()) {
		auto v = q.front(); q.pop();
		ans[v[0]] = min(ans[v[0]], v[3]);
		ans[v[1]] = min(ans[v[1]], v[3]);
		ans[v[2]] = min(ans[v[2]], v[3]);
		for (int i = 0; i < 3; ++i) {
			if (v[i] == 0) continue;
			for (int j = 0; j < 3; ++j) {
				if (i == j or v[j] == cap[j]) continue;
				int transfer = min(v[i], cap[j] - v[j]);
				array<int, 4> v2;
				v2[i] = v[i] - transfer, v2[j] = v[j] + transfer, v2[3-i-j] = v[3-i-j], v2[3] = v[3]+1;
				ll h = hsh(v2[0], v2[1], v2[2]);
				if (dist.count(h)) continue;
				dist[h] = v[3]+1;
				q.push(v2);
			}
		}
	}
	for (int i = 0; i <= max({cap[0], cap[1], cap[2]}); ++i) cout << (ans[i] == pot*6969 ? -1 : ans[i]) << ' ';
	cout << endl;
}
