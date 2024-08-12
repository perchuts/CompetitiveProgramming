#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

void solve() {
	int h, w, Y; cin >> h >> w >> Y;
	vector<vector<int>> grid(h, vector<int>(w));
	for (auto& x : grid) for (auto& z : x) cin >> z;
	vector<int> ans(Y + 1);
	vector<vector<int>> dist(h, vector<int>(w, inf));
	priority_queue<iii, vector<iii>, greater<iii>> pq;
	for (int i = 0; i < h; ++i) dist[i][0] = grid[i][0], dist[i][w-1] = grid[i][w-1];
	for (int i = 0; i < w; ++i) dist[0][i] = grid[0][i], dist[h-1][i] = grid[h-1][i];
	for (int i = 1; i < w - 1; ++i) {
		pq.push({grid[0][i], 0, i});
		pq.push({grid[h-1][i], h-1, i});
	}
	for (int i = 1; i < h - 1; ++i) {
		pq.push({grid[i][0], i, 0});
		pq.push({grid[i][w-1], i, w-1});
	}
	pq.push({grid[0][0], 0, 0});
	pq.push({grid[h-1][0], h-1, 0});
	pq.push({grid[0][w-1], 0, w-1});
	pq.push({grid[h-1][w-1], h-1, w-1});
	vector<int> a = {1, -1, 0, 0, 0, 0, -1, 1};
	while (!pq.empty()) {
		auto [d, x, y] = pq.top();
		pq.pop();
		if (d > dist[x][y]) continue;
		for (int i = 0; i < 4; ++i) {
			int x2 = x + a[i];
			int y2 = y + a[i + 4];
			if (min(x2, y2) >= 0 && x2 < h && y2 < w && ckmin(dist[x2][y2], max(d, grid[x2][y2]))) {
				pq.push({dist[x2][y2], x2, y2});
			}
		}
	}
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			if (dist[i][j] <= Y) ans[dist[i][j]]++;
		}
	}
	int tot = 0;
	for (int i = 1; i <= Y; ++i) {
		tot += ans[i];
		cout << h * w - tot  << endl;
	}
}

int32_t main() {_
	int t = 1; //cin >> t;
	while(t--) solve();
}
