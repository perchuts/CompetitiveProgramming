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

int help[1024], pc[1024];

void solve(){
	int n, m, k; cin >> n >> m >> k;
	vector<int> a(n), b(m);
	for (auto& x : a) cin >> x;
	for (auto& x : b) cin >> x;
	for (int i = 0; i < (1<<m); ++i) {
		int cur = (1LL << 30) - 1;
		for (int j = 0; j < m; ++j) {
			if (i >> j & 1) cur &= b[j];
		}
		help[i] = cur;
	}
	vector<vector<int>> best(n, vector<int>(m+1, 1e18));
	for (int i = 0; i < n; ++i) for (int mask = 0; mask < (1 << m); ++mask) ckmin(best[i][pc[mask]], help[mask]&a[i]);
	int l = 0, r = 1e10, opt = r;
	auto solve = [&] (int pen) {
		ii lst = {0, 0};	
		for (int i = 0; i < n; ++i) {
			ii z = {1e18, 0};
			for (int j = 0; j <= m; ++j) {
				if (ckmin(z.first, lst.first + best[i][j] + pen*j)) z.second = lst.second+j;	
				else if (z.first == lst.first + best[i][j] + pen*j) ckmin(z.second, lst.second+j);
			}
			lst = z;
		}
		return lst; 
	};
	assert(solve(r).second == 0);
	while (l <= r) {
		int md = l + (r-l+1)/2;
		if (solve(md).second <= k) opt = md, r = md-1;
		else l = md+1;
	}
	auto [x2, y2] = solve(opt-1);
	cout << x2 - y2 * (opt-1) + (y2-k) * (opt) << endl;
}

int32_t main(){_
	for (int i = 0; i < 1024; ++i) pc[i] = __builtin_popcount(i);
  int t = 1; cin >> t;
  while(t--) solve();
}
