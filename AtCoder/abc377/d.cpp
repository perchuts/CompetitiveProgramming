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
	vector<ii> fodase(n);
	vector<int> comeco(m+1, 1), fim(m+1, m);
	for (auto& [x, y] : fodase) {
		cin >> x >> y;
		ckmin(fim[x], y-1);
		ckmax(comeco[y], x+1);
	}
	// pra dar certo pra [L, R]: L > li ou R < ri
	for (int i = 2; i <= m; ++i) ckmax(comeco[i], comeco[i-1]);
	for (int i = m-1; i >= 1; --i) ckmin(fim[i], fim[i+1]);
	int tot = 0;
	for (int i = 1; i <= m; ++i) {
		int l = i, r = fim[i], ans = i-1;
		while (l <= r) {
			int md = l + (r-l+1)/2;
			if (comeco[md] <= i) ans = md, l = md+1;
			else r = md-1;
		}
		tot += ans-i+1;
	}
	cout << tot << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
