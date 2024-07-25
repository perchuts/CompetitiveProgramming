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

void solve(){
 	int n; cin >> n;
	vector<array<int, 4>> v(n);
	for (auto& x : v) cin >> x[0] >> x[1] >> x[2] >> x[3];
	int p; cin >> p;
	int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
	mt19937 rng(time(0));
	auto rnd = [&] (int l, int r) {
		uniform_int_distribution<int> uid(l, r);
		return uid(rng);
	};
	for (int j = 0; j < n; ++j) {
		if (v[j][0] == v[j][2]) {
			if (v[j][1] > v[j][3]) swap(v[j][1], v[j][3]);
		} else {
			if (v[j][0] > v[j][2]) swap(v[j][0], v[j][2]);
		}
	}
	vector<int> dists;
	int lim = 2e7/n;
	for (int i = 0; i < lim; ++i) {
		int X = rnd(x1, x2), Y = rnd(y1, y2);
		int mn = 1e17;
		for (int j = 0; j < n; ++j) {
			if (v[j][0] == v[j][2]) {
				if (v[j][1] <= Y && Y <= v[j][3]) ckmin(mn, abs(X - v[j][0]));	
				else if (Y < v[j][1]) ckmin(mn, ceil(hypot(X-v[j][0],Y-v[j][1])));
				else ckmin(mn, ceil(hypot(X-v[j][2],Y-v[j][3]))); 
			} else {
				if (v[j][0] <= X && X <= v[j][2]) ckmin(mn, abs(Y - v[j][1]));
				else if (X < v[j][0]) ckmin(mn, ceil(hypot(]X-v[j][0],Y-v[j][1])));
				else ckmin(mn, ceil(hypot(X-v[j][2],Y-v[j][3]))); 
			}
		}
		dists.pb(mn);
	}
	sort(all(dists));	
	double id = lim/(double)100 * p;
	int x = ceil(id);
	cout << dists[x] << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
