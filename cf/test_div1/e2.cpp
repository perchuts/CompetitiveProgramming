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
	vector<int> w(n), p(n);
	vector<double> pp(n);
	for (int i = 0; i < n; ++i) {
		cin >> p[i] >> w[i];
		pp[i] = p[i] / 100.0;
	}
	double ans = 0;
	int m = 0;
	for (int i = 0; i < (1 << n); ++i) {
		int S = 0; double P = 1;
		for (int j = 0; j < n; ++j) {
			if ((i >> j) & 1) S += w[j], P *= pp[j];
		}		
		if (__builtin_popcount(i) == 1) cout << i << ' ' << S * P << endl;
		if (ckmax(ans, S * P)) m = i;
	}
	
	cout << fixed << setprecision(6) << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
