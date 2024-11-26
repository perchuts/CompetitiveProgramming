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
	vector<int> v(m);
	for (auto& x : v) cin >> x;
	reverse(begin(v), end(v));
	vector<vector<int>> mark(n+1);
	vector<int> temp(n+1);
	vector<int> ans(n+1);
	for (int i = 1; i <= n; ++i) {
		sort(all(mark[i]));
		for (auto x : mark[i]) temp[x] = 1;
		bool ok = 0;
		for (int j = 0; j < m; ++j) {
			if (temp[v[j]] == 0) {
				ok = 1;
				ans[i] = v[j];
				break;
			}
		}
		if (!ok) {
			cout << -1 << endl;
			return;
		}
		for (auto x : mark[i]) temp[x] = 0;
		for (int j = 2 * i; j <= n; j += i) mark[j].pb(ans[i]); 
	}
	for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
	cout << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
