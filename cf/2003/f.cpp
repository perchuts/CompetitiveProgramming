#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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

int bit[5][3005], n;

void insert(int id, int x, int k) {
	for ( ; x <= n; x += (x)&(-x)) ckmax(bit[id][x], k);
}

int query(int id, int x) {
	int ans = -100000;
	while (x) ckmax(ans, bit[id][x]), x -= x&(-x);
	return ans;
}

void solve(){
 	int m; cin >> n >> m;
	vector<int> a(n), b(n), c(n);
	for (auto& x : a) cin >> x;
	for (auto& x : b) cin >> x;
	for (auto& x : c) cin >> x;
	const int tries = 5*5*5*5*5*5;
	int ans = -1;
	vector<int> p(n+1);
	mt19937 rng(time(0));
	for (int __ = 0; __ < tries; ++__) {
		for (int i = 1; i <= n; ++i) p[i] = rng() % m;
		for (int i = 0; i < m-1; ++i) for (int j = 1; j <= n; ++j) bit[i][j] = -100000;
		for (int i = 0; i < n; ++i) {
			int val = p[b[i]], my = 0;
			if (val == 0) my = c[i];
			else my = query(val-1, a[i]) + c[i];
			if (my > 0) {
					insert(val, a[i], my);
					if (val == m-1) ckmax(ans, my);
			}
		}
	}
	cout << ans << endl;
}
int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
