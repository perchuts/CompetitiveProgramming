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
const int mod = (119<<23)+1;
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
	vector<vector<int>> v(2, vector<int>(n));
	for (auto& x : v) for (auto& y : x) cin >> y;
	vector<vector<int>> onde(2, vector<int>(n));
	vector<vector<int>> vals(2, vector<int>(n));
	vector<map<int, set<ii>>> mp(2);

	for (int i = 0; i < 2; ++i) {
		iota(all(onde[i]), 0);
		sort(all(onde[i]), [&] (int x, int y) {
			return v[i][x] < v[i][y];
		});
		vector<int> temp(n);
		for (int j = 0; j < n; ++j) temp[onde[i][j]] = j;
		swap(temp, onde[i]);
		for (int j = 0; j < n; ++j) vals[i][onde[i][j]] = v[i][j], mp[i][v[i][j]].insert({onde[i][j], j});
	}
	auto inv = [&] (int b, int e = mod - 2) {
		int ans = 1;
		while (e) {
			if (e&1) ans = ans * b % mod;
			b = b * b % mod, e /= 2;
		}
		return ans;
	};
	int ans = 1;
	for (int i = 0; i < n; ++i) ans = ans * min(vals[0][i], vals[1][i]) % mod;
	cout << ans << ' ';
			//cout << endl;
			//for (auto a : vals) {
			//	for (auto b : a) cout << b << ' ';
			//	cout << endl;
			//}
	while (q--) {
		int o, x; cin >> o >> x;
		--x, --o;

		int val = v[o][x];
		auto lst = *prev(end(mp[o][val]));
		if (lst.second != x) {
			mp[o][val].erase(lst);
			mp[o][val].erase({onde[o][x], x});
			ans = ans * inv(min(vals[0][onde[o][lst.second]], vals[1][onde[o][lst.second]])) % mod;
			swap(onde[o][lst.second], onde[o][x]);
			vals[o][onde[o][x]]++;
			v[o][x]++;
			ans = ans * min(vals[0][onde[o][x]], vals[1][onde[o][x]]) % mod;
			mp[o][val].insert({onde[o][lst.second], lst.second});
			mp[o][val+1].insert({onde[o][x], x});
		} else {
			mp[o][val].erase(lst);
			ans = ans * inv(min(vals[0][onde[o][lst.second]], vals[1][onde[o][lst.second]])) % mod;
			vals[o][onde[o][x]]++;
			v[o][x]++;
			ans = ans * min(vals[0][onde[o][x]], vals[1][onde[o][x]]) % mod;
			mp[o][val].erase({onde[o][x], x});
			mp[o][val+1].insert({onde[o][x], x});
		}
		cout << ans << ' ';
	}
	cout << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
