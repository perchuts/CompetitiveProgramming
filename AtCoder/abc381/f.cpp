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
const int mod = (119<<23)+1;
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
	vector<int> a(n);
	for (auto& x : a) cin >> x;
	vector<vector<int>> ultima(n+1, vector<int>(21, n));
	for (int i = n-1; i >= 0; --i) {
		for (int j = 1; j <= 20; ++j) {
			if (a[i] == j) ultima[i][j] = i;
			else ultima[i][j] = ultima[i+1][j];
		}
	}
	// dp[mask] = menor lugar pra terminar a mascara
	int ans = 0;
	vector<int> dp((1<<21), n);
	dp[0] = -1;
	for (int i = 1; i < (1 << 21); ++i) {
		dp[i] = n;
		for (int j = 1; j <= 20; ++j) {
			if (i >> j & 1) {
				int k = dp[i - (1 << j)];
				if (k >= n-2) continue;
				int p1 = ultima[k+1][j];
				if (p1 == n) continue;
				p1 = ultima[p1+1][j];
				ckmin(dp[i], p1);
			}
		}
		if (dp[i] != n) ckmax(ans, 2 * __builtin_popcount(i));
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
