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

	vector<pair<double, int>> bet(n);

	for (auto& [x, y] : bet) cin >> x >> y;

	vector<pair<double, int>> tmp;

	sort(bet.rbegin(), bet.rend());

	for (int i = 0; i < n; ++i) {
		if (tmp.empty() || tmp.back().first != bet[i].first) tmp.pb(bet[i]);
		else tmp.back().second += bet[i].second;
	}

	swap(tmp, bet);

	n = sz(bet);


	vector<double> pref(n+1), suf(n+2);

	for (int i = 1; i <= n; ++i) pref[i] = pref[i-1] + bet[i-1].second;
	for (int i = n; i >= 1; --i) suf[i] = suf[i+1] + bet[i-1].second;

	double ans = 0;

	int ii, jj;
	
	auto f = [&] (int i, int j) {
		assert(i < j);
		if (i == 0) {
			return suf[j] - suf[j]/(1.0-bet[j-1].first);
		}
		assert(i > 0);
		double val = pref[i] + suf[j] - max(pref[i]/bet[i-1].first, suf[j]/(1.0-bet[j-1].first));
		ckmax(ans, val);
		return val;
	};

	for (int i = 1; i <= n; ++i) {
		int l = 0, r = i-1;
		while (r-l > 2) {
			int m1 = l + (r-l)/3, m2 = r - (r-l)/3;
			if (f(m1, i) < f(m2, i)) l = m1;
			else r = m2;
		}
		for (int j = l; j <= r; ++j) f(j, i);
	}

	cout << fixed << setprecision(10) << ans << endl;

}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
