#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
	int n, q; cin >> n >> q;
	vector<pair<char, int>> moves(q);
	for (auto& [x, y] : moves) cin >> x >> y, --y;
	map<ii, int> dp;
	dp[{0, 1}] = 0;
	for (int i = 0; i < q; ++i) {
		map<ii, int> ndp;
		int type = moves[i].first == 'R', pos = moves[i].second;
		auto add = [&] (int x, int y, int k) {
			if (type) swap(x, y);
			if (ndp.count({x, y})) ckmin(ndp[{x, y}], k);
			else ndp[{x, y}] = k;
		};
		for (auto [p, steps] : dp) {
			auto [x, y] = p; 
			if (type) swap(x, y);
			// +1
			if (x < y and y <= pos) {
				// x ... y .... pos
				int cost = pos-y+1 + pos-x;
				add(pos, (pos+1)%n, cost+steps);
			} else if (y <= pos and pos < x) {
				// ... y .. pos ... x 
				int cost = pos-y+1 + n-(x-pos);
				add(pos, (pos+1)%n, cost+steps);
			} else if (pos < x and x < y) {
				// pos ... x ... y
				int cost = n-(y-pos)+1 + n-(x-pos);
				add(pos, (pos+1)%n, cost+steps);
			} else if (x <= pos) {
				// x .. pos
				int cost = pos-x;
				add(pos, y, cost+steps);
			} else {
				// pos .. x
				int cost = n-(x-pos);
				add(pos, y, cost+steps);
			}
			// -1
			if (pos <= y and y < x) {
				// pos ... y .... x 
				int cost = y-pos+1 + x-pos; 
				add(pos, (pos+n-1)%n, cost+steps);
			} else if (x < pos and pos <= y) {
				// ... x .. pos ... y
				// parte do y, parte do x
				int cost = y-pos+1 + n-(pos-x);
				add(pos, (pos+n-1)%n, cost+steps);
			} else if (y < x and x < pos) {
				// y ... x ... pos
				int cost = n-(pos-y)+1 + n-(pos-x);
				add(pos, (pos+n-1)%n, cost+steps);
			} else if (x <= pos) {
				// x .. pos
				int cost = n-(pos-x);
				add(pos, y, cost+steps);
			} else {
				// pos .. x
				int cost = x-pos;
				add(pos, y, cost+steps);
			}
		}
		swap(dp, ndp);
	}
	int ans = 1e9;
	for (auto [x, y] : dp) ckmin(ans, y);
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
