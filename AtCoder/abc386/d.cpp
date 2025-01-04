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
	int n, m; cin >> n >> m;
	vector<iii> v(m);
	multiset<int> mt;
	for (auto& [x, y, z] : v) {
		cin >> x >> y;
		char c; cin >> c;
		z = (c == 'B');
		if (z) mt.insert(y);
	}
	sort(all(v));
	for (int l = 0, r = 0; l < m; l = r) {
		auto [x0, y0, z0] = v[l];
		while (r < m) {
			auto [x, y, z] = v[r];
			if (x != x0) break; 
			r++;
		}

		for (int i = l; i < r; ++i) {
			auto [x, y, z] = v[i];
			if (z == 0) {
				if (!mt.empty()) {
					auto k = *prev(end(mt));
					if (k >= y) {
						cout << "No" << endl;
						exit(0);
					}
				}
			}
		}
		for (int i = l; i < r; ++i) {
			auto [x, y, z] = v[i];
			if (z) mt.erase(mt.find(y));
		}
	}
	cout << "Yes" << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
