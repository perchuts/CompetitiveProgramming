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
	int n, m; cin >> n >> m;
	vector<vector<int>> pw(m+1, vector<int>(n*n+5));
	vector<vector<int>> ncr(n+1, vector<int>(n+1));
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (i == j or j == 0) ncr[i][j] = 1;
			else ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % mod;
		}
	}
	for (int i = 1; i <= m; ++i) {
		pw[i][0] = 1;
		for (int j = 1; j <= n * n; ++j) pw[i][j] = pw[i][j-1] * i % mod;
	}
	pw[0][0] = 1;
	vector<vector<int>> f(n+1, vector<int>(m+1));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			f[i][j] = pw[m][i*(i-1)/2];
			for (int s = 1; s < i; ++s) {
				int tira = ncr[i-1][s-1] * f[s][j] % mod * pw[m-j][s*(i-s)] % mod * pw[m][(i-s)*(i-s-1)/2] % mod;
				f[i][j] = (f[i][j] - tira + mod) % mod;
			}
		}
	}
	int ans = (n-1-m) * pw[m][n*(n-1)/2] % mod;
	ans = (ans + mod) % mod;
	for (int k = 1; k <= m; ++k) {
		for (int s = 1; s <= n; ++s) {
			int add = ncr[n][s] * f[s][k] % mod * pw[m-k][s*(n-s)] % mod * pw[m][(n-s)*(n-s-1)/2] % mod;
			ans = (ans + add) % mod;
		}
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
