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
	int n, m, k; cin >> n >> m >> k;
	vector<vector<int>> v(n, vector<int>(m));
	vector<map<int, int>> freq(n);
	for (auto& x : v) for (auto& y : x) cin >> y;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (v[i][j] == -1) freq[i][-1]++;
			else {
				if (i != 0) freq[i-1][v[i][j]]++;
				if (i != n-1) freq[i+1][v[i][j]]++;
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (v[i][j] != -1) ans += freq[i][v[i][j]];
	ans /= 2;
	for (int i = 0; i < n-1; ++i) ans += freq[i][-1] * freq[i+1][-1];
	vector<int> dp(k+1);
	int best = 0, upd = 0;
	for (int i = 0; i < n; ++i) {
		int c = freq[i][-1];
		for (auto [color, qnt] : freq[i]) if (color != -1) {
			ckmax(dp[color], upd);
			dp[color] += qnt * c, ckmax(best, dp[color]); 
		}
		int my = best;
		if (i != n-1) my -= freq[i][-1] * freq[i+1][-1]; 
		ckmax(upd, my);
	}
	cout << upd + ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
