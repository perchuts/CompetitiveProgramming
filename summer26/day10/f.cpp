#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back
using namespace std;

using ll = long long;

int32_t main() {_
	int t; cin >> t;
	vector<int> pw(31, 1);
	for (int i = 1; i <= 30; ++i) pw[i] = 4 * pw[i-1];
	for (int tt = 1; tt <= t; ++tt) {
		cout << "Case #" << tt << ": ";
		cout << fixed << setprecision(10);
		map<int, int> vis;
		int m, n; cin >> m >> n;
		vector<array<double, 4>> sexo(n);
		for (int i = 0; i < n; ++i) for (int j = 0; j < 4; ++j) cin >> sexo[i][j];
		for (int i = 0; i < n; ++i) sort(rbegin(sexo[i]), rend(sexo[i]));
		priority_queue<pair<double, int>> pq;
		double pp = 1;
		for (int i = 0; i < n; ++i) pp *= sexo[i][0];
		pq.push({pp, 0});
		double ans = 0;
		for (int j = 0; j < min(pw[n], m); ++j) {
			auto [P, mask] = pq.top(); pq.pop();
			ans += P;
			for (int i = 0; i < n; ++i) {
				int val = (mask >> (2 * i)) % 4;
				int z = mask + pw[i];
				if (val != 3 and vis[z] == 0) {
					vis[z] = 1;
					double np = P;
					if (sexo[i][val] != 0) np /= sexo[i][val];
					np *= sexo[i][val+1];
					pq.push({np, z});
				}
			}
		}
		cout << ans << endl;
	}
}
