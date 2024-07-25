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
	vector<int> v(n);
	for (auto& x : v) cin >> x;
	vector<int> pot(60, 1);
	vector<vector<bool>> pr(n, vector<bool>(60));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 60; ++j) {
			int mee = ((v[i]>>j)&1);
			if (i == 0) pr[i][j] = mee;
			else pr[i][j] = pr[i-1][j] ^ mee;
		}
	}
	for (int i = 1; i < 60; ++i) pot[i] = pot[i-1] * 2 % mod;
	int x = 0;
	vector<vector<int>> sum(2, vector<int>(60));
	for (int j = 59; j < 60; ++j) {
		for (int w = 0; w <= j; ++w) sum[0][w] = 1, sum[1][w] = 0;
		for (int i = 0; i < n; ++i) {
			x = 0;
			for (int w = 0; w <= j; ++w) x = (x + sum[pr[i][w]^1][w] * pot[w]) % mod;
			for (int w = 0; w <= j; ++w) sum[pr[i][w]][w] = (sum[pr[i][w]][w] + x) % mod;
		}
	}
	cout << x << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
