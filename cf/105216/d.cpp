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

int32_t main(){_
	int q; cin >> q;
	vector<vector<int>> dp(801, vector<int>(1601*9));
	int shift = 800 * 9; 
	dp[0][shift] = 1;
	for (int i = 1; i <= 800; ++i) {
		for (int j = 0; j <= 9 * i; ++j) {
			for (int dif = -9; dif <= 9; ++dif) {
				if (dif == 0) continue;
				int antes = j - dif;
				if (-9 * (i-1) <= antes and antes <= 9 * (i-1)) {
					dp[i][j+shift] += dp[i-1][antes+shift] * (9 - abs(dif) + 1);
					dp[i][j+shift] %= mod;
				}
			}
			dp[i][-j+shift] = dp[i][j+shift];
		}
	}	
	while (q--) {
		int n; cin >> n;
		int ans = dp[n][shift];
		for (int i = 1; i <= 9; ++i) {
			ans -= dp[n-1][shift+i];
			ans -= dp[n-1][shift-i];
			ans %= mod;
			ans += mod;
			ans %= mod;
		}
		cout << ans << endl;
	}
}
