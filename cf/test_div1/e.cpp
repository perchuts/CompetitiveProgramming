#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
#define double long double

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
	int S = 0;
	double P = 1;
	for (int i = 0; i < n; ++i) {
		cin >> p[i] >> w[i];
		pp[i] = p[i] / 100.0;
		S += w[i], P *= pp[i];
	}
	double ans = S * P;
	vector<vector<int>> fs(101);
	vector<int> ptr(101);
	vector<vector<pair<double, double>>> ps(101);
	for (int i = 0; i < n; ++i) fs[p[i]].pb(i);
	for (int i = 1; i <= 100; ++i) {
		sort(all(fs[i]), [&] (int a, int b) {
			return w[a] * p[b] > w[b] * p[a];
		});
		ps[i].resize(sz(fs[i]));
		for (int j = 0; j < sz(fs[i]); ++j) {
			int id = fs[i][j];
			if (j == 0) ps[i][j] = {w[id], pp[id]};
			else ps[i][j].first = w[id] + ps[i][j-1].first, ps[i][j].second = ps[i][j-1].second * pp[id];
		}
		ptr[i] = sz(fs[i])-1;
	}
	double cs = S;
	for (int __ = 0; __ < n-1; ++__) {
		int best = -1;
		double val = -1e18;
		for (int i = 1; i <= 100; ++i) {
			if (fs[i].empty()) continue;
			int j = fs[i].back();
			if (ckmax(val, cs/pp[j] - w[j]/(double)pp[j])) best = i;
			if (__ == 0) cout << j << ' ' << cs/pp[j] - w[j] / pp[j] << endl;
		}
		// P * S -> P / pp[j] * (S - w[j]) > P / pp[k] * (S - w[k])
		// S / pp[j] - w[j] / pp[j] > S / pp[k] - w[k] / pp[k]
		ptr[best]--;
		cout << fs[best].back() << ' ';
		S = 0, P = 1;
		for (int i = 1; i <= 100; ++i) {
			if (ptr[i] != -1) S += ps[i][ptr[i]].first, P *= ps[i][ptr[i]].second;
		}
		cs = S;
		fs[best].pop_back();
		ckmax(ans, S * P);
	}
	cout << endl;
	cout << fixed << setprecision(6) << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
