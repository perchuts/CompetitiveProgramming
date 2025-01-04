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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

ii dir[300];

void solve(){
	int n, m; cin >> n >> m;
	vector<string> grid(n);
	for (auto& x : grid) cin >> x;
	dir['L'] = {0, -1};
	dir['R'] = {0, 1};
	dir['U'] = {-1, 0};
	dir['D'] = {1, 0};
	vector<vector<int>> good(n, vector<int>(m)), vis = good;
	vector<vector<ii>> f(n, vector<ii>(m));
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
		if (grid[i][j] == '?') continue;
		auto [x, y] = dir[grid[i][j]];
		int x2 = i + x, y2 = j + y;
		f[i][j] = {x2, y2};
	}
	auto go = [&] (auto&& self, int i, int j) {
		if (min(i, j) < 0 or i == n or j == m) return 1ll;
		if (grid[i][j] == '?') return 0ll;
		if (vis[i][j]) return good[i][j];
		vis[i][j] = 1;
		return good[i][j] = self(self, f[i][j].first, f[i][j].second);
	};
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (!vis[i][j]) go(go, i, j);
		}
	}
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (grid[i][j] == '?') {
				if (i != 0 and good[i-1][j] == 0) ans++;
				else if (j != 0 and good[i][j-1] == 0) ans++;
				else if (i != n-1 and good[i+1][j] == 0) ans++;
				else if (j != m-1 and good[i][j+1] == 0) ans++;
			} else {
				if (good[i][j] == 0) ans++;
			}
		}	
	}		
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
