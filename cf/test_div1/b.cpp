#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
	vector<ii> ans;
	int n; cin >> n;
	vector<ii> v(n);
	for (auto& [x, y] : v) cin >> x >> y;
	sort(all(v));
	vector<int> p(n); iota(all(p), 0);
	sort(all(p), [&] (int a, int b) {
		auto [x1, y1] = v[a];
		auto [x2, y2] = v[b];
		if (max(x1, y1) != max(x2, y2)) return max(x1, y1) < max(x2, y2);
		return min(x1, y1) < min(x2, y2);
	});
	for (int j = 0; j< n; ++j) {
		int i = p[j];
		cout << v[i].first << ' ' << v[i].second << ' ';
	}
	cout << endl;
}

int32_t main(){_
	int tt; cin >> tt;
	while (tt--) solve();
}
