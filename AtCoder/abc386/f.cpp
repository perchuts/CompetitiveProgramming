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
	int k; cin >> k;
	string s, t; cin >> s >> t;
	int n = sz(s), m = sz(t);
	vector<vector<int>> dp(n+1, vector<int>(3*k+10, inf));
	auto get = [&] (int i, int j) {
		return dp[i][j-i+k+3];
	};
	auto mn = [&] (int i, int j, int x) {
		if (abs(i-j) > k) return;
		ckmin(dp[i][j-i+k+3], x);
	};
	for (int i = 0; i <= n; ++i) mn(i, 0, i);
	for (int i = 0; i <= m; ++i) mn(0, i, i);
	for (int i = 1; i <= n; ++i) {
		for (int j = max(1ll, i-k); j <= min(m, i+k); ++j) {
			// match
			if (s[i-1] == t[j-1]) mn(i, j, get(i-1, j-1));
			// delete up
			mn(i, j, get(i-1, j)+1);
			// delete down (equivalent to insert)
			mn(i, j, get(i, j-1)+1);
			// replace
			mn(i, j, get(i-1, j-1)+1);
			
			int val = get(i, j);
			if (val + n-i + m-j <= k) {
				cout << "Yes" << endl;
				return;
			}
		}
	}
	cout << "No" << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
