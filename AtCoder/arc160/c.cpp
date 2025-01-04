#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int long long

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = (119<<23)+1;
const int maxn = 3e5+100;
const int lgmax = 30;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

void solve(){
	int n, mxval = 0; cin >> n;
	vector<int> v(n);
	for (auto& x : v) cin >> x, ckmax(mxval, x);
	vector<int> freq(mxval+lgmax);
	for (auto x : v) freq[x]++;
	// note que soma(2^a[i]) eh constante! 
	vector<vector<int>> dp = {{1}};	
	int mxp = 0;
	for (int i = 1; i < mxval+lgmax; ++i) {
		dp.push_back(vector<int>(mxp+1));
		for (int p = 0; p <= mxp; ++p) {
			int w = max(0ll, 2*p-freq[i-1]);
			if (w < sz(dp[i-1])) dp[i][p] = dp[i-1][w];
		}
		for (int p = mxp-1; ~p; --p) {
			dp[i][p] += dp[i][p+1];
			if (dp[i][p] >= mod) dp[i][p] -= mod;
		}
		mxp += freq[i], mxp /= 2;
	}
	assert(dp.back()[0] < mod);
	cout << dp.back()[0] << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
