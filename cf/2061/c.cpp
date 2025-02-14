#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define stress

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

int solve(int n, vector<int> v){
	vector<vector<int>> dp(n, vector<int>(3));
	dp[n-1][1] = 1;
	dp[n-1][0] = (n/2 >= v.back());
	for (int i = n-2; i >= 0; --i) {
		int x = v[i], y = v[i+1];
		if (x == y) {
			// eu falo verdade, ele tbm
			dp[i][0] += dp[i+1][0];
			// eu falo verdade, ele mente
			if (i == n-2) dp[i][0]++;
			else if (v[i+2] == x+1) dp[i][0] += dp[i+2][0];
			if (y) dp[i][1] = dp[i+1][0];
		} else {
			// nao da pra nos 2 falar verdade ao mesmo tempo
			// eu falo verdade, ele mente
			if (i == n-2) dp[i][0] = 1;
			else if (v[i+2] == x+1) dp[i][0] += dp[i+2][0];
			// eu falo mentira, ele fala verdade
			if (y) dp[i][1] = dp[i+1][0];
		}
		dp[i][0] %= mod;
		dp[i][1] %= mod;
		if ((i+1)/2 < x) dp[i][0] = 0;
		//cout << dp[i][0] << ' ' << dp[i][1] << endl;
	}
	return (dp[0][0] + dp[0][1]) % mod;
}

int brute(int n, vector<int> v) {
	int ans = 0;
	for (int i = 0; i < (1 << n); ++i) {
		int lst = 0, ok = 1, qt = 0;
		for (int j = 0; j < n; ++j) {
			int val = (i >> j) & 1;
			if (lst == 1 and val == 1) ok = 0;
			if (val == 0) ok &= (v[j] == qt);
			lst = val;
			qt += val;	
		}
		ans += ok;
	}
	return ans;
}

int32_t main(){_
#ifdef stress
	int t = 1;
	while (true) {
	int n = rnd(1, 4);
	vector<int> v(n);
	for (auto& x : v) x = rnd(0, n);
	int my = solve(n, v);
	int br = brute(n, v);
	if (my != br) {
		cout << n << endl;
		for (auto x : v) cout << x << ' ';
		cout << endl;
		cout << my << endl;
		cout << "correct: " << br << endl;
		exit(0);
	}
	}
	cout << "AC " << t++ << endl;
#else
  int t = 1; cin >> t;
  while(t--) {
	  int n; cin >> n;
	  vector<int> v(n);
	  for (auto& x : v) cin >> x;
	  cout << solve(n, v) << endl;
  }
#endif
}
