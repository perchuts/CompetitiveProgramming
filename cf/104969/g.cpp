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
	int n; cin >> n;
	vector<ii> v(n);
	for (auto& [x, y] : v) cin >> x >> y;
	while (true) {
		int i = rnd(0, n-1), j;
		while (true) {
			j = rnd(0, n-1);
			if (i != j) break;
		}
		int cnt = 2;
		for (int k = 0; k < n; ++k) {
			if (k == i or k == j) continue;
			int x1 = v[i].first - v[k].first, y1 = v[i].second - v[k].second;
			int x2 = v[j].first - v[k].first, y2 = v[j].second - v[k].second;
			if (x1 * y2 - x2 * y1 == 0) cnt++;
		}
		if (cnt >= n/8) {
			// W
			int xi = v[i].first, yi = v[i].second;
			int xj = v[j].first, yj = v[j].second;
			cout << yi - yj << " " << xj - xi << " " << xj*yi - xi*yj << endl;
			exit(0);
		}
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
