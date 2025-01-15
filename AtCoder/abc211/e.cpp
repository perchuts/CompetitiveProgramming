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


void solve(){
	int n, k; cin >> n >> k;
	vector<vector<int>> grid(n, vector<int>(n));
	for (auto& x : grid) for (auto& y : x) {
		char c; cin >> c;
		y = (c == '#');
	}
	int ans = 0;
	unordered_set<ull> s;
	vector<ii> pos(k);
	vector<int> a = {1, -1, 0, 0, 0, 0, 1, -1};
	auto brute = [&] (auto&& self, int qnt, ull mask) -> void {
		if (qnt == k) {
			ans++;
			return;
		}
		for (int j = 0; j < qnt; ++j) {
			auto [x, y] = pos[j];
			for (int z = 0; z < 4; ++z) {
				int x2 = x + a[z], y2 = y + a[z+4];
				int posbit = 8 * x2 + y2;
				if (min(x2, y2) < 0 or max(x2, y2) == n or grid[x2][y2]) continue;
				if (mask >> posbit & 1) continue;
				ull nmask = mask | (1ULL << posbit);
				if (s.find(nmask) != end(s)) continue;
				s.insert(nmask);
				pos[qnt] = {x2, y2};
				self(self, qnt+1, nmask);
			}
		}

	};
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (grid[i][j] == 0) pos[0] = {i, j}, brute(brute, 1, (1ULL << (8*i + j)));
		}
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
