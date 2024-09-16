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

void solve() {
	int n, k; cin >> n >> k;
	struct f {
		int a, b;
		f(int a_, int b_) : a(a_), b(b_) {}
		f() {}
	};
	vector<f> v(n);
	for (auto& [x, y] : v) cin >> x >> y;
	vector<vector<int>> dp(n+1, vector<int>(k+1, 1)); // min, max
	sort(all(v), [] (f x, f y) {
		return (x.a-1)*y.b<(y.a-1)*x.b; 
	});
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= k; ++j) {		
			dp[i][j] = max(dp[i-1][j], v[i-1].a*dp[i-1][j-1] + v[i-1].b);
		}
	}
	cout << dp[n][k] << endl;
}

int32_t main() {_
	int t = 1; //cin >> t;
	while(t--) solve();
}