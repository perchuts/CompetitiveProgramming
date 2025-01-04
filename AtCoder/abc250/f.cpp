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
int triangle(ii a, ii b, ii c) {
	ii x = {b.first - a.first, b.second - a.second};
	ii y = {c.first - a.first, c.second - a.second};
	return 4 * abs(x.first * y.second - x.second * y.first);
}

void solve(){
	int n; cin >> n;
	vector<ii> v(n);
	for (auto& [x, y] : v) cin >> x >> y;
	int ptr = 1, area = 0, tot_area = 0;
	for (int i = 1; i < n - 1; ++i) tot_area += triangle(v[0], v[i], v[i+1]) / 4;
	int ans = tot_area;
	int cur_d = tot_area;
	for (int i = 0; i < n; ++i) {
		while (true) {
			int tr = triangle(v[i], v[ptr%n], v[(ptr+1)%n]);
			if (ckmin(cur_d, abs(tr + area - tot_area))) area += tr, ptr++;
			else break;
		}
		ckmin(ans, cur_d);
		area -= triangle(v[i], v[(i+1)%n], v[ptr%n]);
		cur_d = abs(area - tot_area); 
		ckmin(ans, cur_d);
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}

