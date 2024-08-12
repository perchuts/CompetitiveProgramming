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

void solve() {
	int n; cin >> n;
	int mn = 0, mx = 0;
	vector<ii> intr(n);
	for (auto& [x, y] : intr) {
		cin >> x >> y;
		mn += x, mx += y;
	}
	if (mn > 0 || mx < 0) {
		cout << "No" << endl;
	} else {
		cout << "Yes" << endl;
		vector<int> ans(n);
		for (int i = 0; i < n; ++i) ans[i] = intr[i].first;
		for (int i = 0; i < n; ++i) {
			int consigo = min(intr[i].second - intr[i].first, -mn);
			mn += consigo;
			ans[i] += consigo;
			cout << ans[i] << ' ';
		}
	}
}

int32_t main() {_
	int t = 1; //cin >> t;
	while(t--) solve();
}
