#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
using namespace std;

using ll = long long;

const int mod = 998244353;
const int inf = 2e9 + 100;
const double PI = acos(-1);

int32_t main() {_
	int n, m;
	cin >> n >> m;
	vector<string> grid(n);
	for (auto &s : grid) cin >> s;
	
	const int MX = 4 * n * m;

	using T = double;
	auto id = [&] (int i, int j, int k) {
		return 4*(i*m + j) + k;
	};
	auto rev = [&] (int id) {
		return tuple<int, int, int>{(id / 4 / m), (id/4) % m, id % 4};
	};

	// T..0..T
	// .     .
	// 1     3
	// .     .
	// T..2..T

	vector<T> dist(MX, 1e9);
	dist[id(0, 0, 0)] = 5;
	dist[id(0, 0, 1)] = 5;
	priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;
	
	pq.emplace(dist[id(0, 0, 0)], id(0, 0, 0));
	pq.emplace(dist[id(0, 0, 1)], id(0, 0, 1));
	while (pq.size()) {
		auto [d, u] = pq.top(); pq.pop();
		if (d > dist[u]) continue;
		auto [i, j, k] = rev(u);
		for (int nk : {(k+1)%4, (k+3)%4}) {
			int v = id(i, j, nk);
			T w = grid[i][j] == 'X' ? 10 : PI*2.5;
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				pq.emplace(dist[v], v);
			}
		}
		if (k == 1) {
			if (j - 1 >= 0) {
				int v = id(i, j - 1, 3);
				T w = 0;
				if (dist[v] > dist[u] + w) {
					dist[v] = dist[u] + w;
					pq.emplace(dist[v], v);
				}
			}
		}
		if (k == 3) {
			if (j + 1 < m) {
				int v = id(i, j + 1, 1);
				T w = 0;
				if (dist[v] > dist[u] + w) {
					dist[v] = dist[u] + w;
					pq.emplace(dist[v], v);
				}
			}
		}
		if (k == 0) {
			if (i - 1 >= 0) {
				int v = id(i - 1, j, 2);
				T w = 0;
				if (dist[v] > dist[u] + w) {
					dist[v] = dist[u] + w;
					pq.emplace(dist[v], v);
				}
			}
		}
		if (k == 2) {
			if (i + 1 < n) {
				int v = id(i + 1, j, 0);
				T w = 0;
				if (dist[v] > dist[u] + w) {
					dist[v] = dist[u] + w;
					pq.emplace(dist[v], v);
				}
			}
		}
		if (k == 1 || k == 3) {
			for (int ni : {i - 1, i + 1}) {
				if (ni < 0 || ni >= n) continue;
				int v = id(ni, j, k);
				T w = 10;
				if (dist[v] > dist[u] + w) {
					dist[v] = dist[u] + w;
					pq.emplace(dist[v], v);
				}
			}
		}
		if (k == 0 || k == 2) {
			for (int nj : {j - 1, j + 1}) {
				if (nj < 0 || nj >= m) continue;
				int v = id(i, nj, k);
				T w = 10;
				if (dist[v] > dist[u] + w) {
					dist[v] = dist[u] + w;
					pq.emplace(dist[v], v);
				}
			}
		}
	}

	T ans = min(dist[id(n - 1, m - 1, 2)], dist[id(n - 1, m - 1, 3)]) + 5;
	cout << fixed << setprecision(9);
	cout << ans << endl;
}
