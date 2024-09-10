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
 	int n, m; cin >> n >> m;
	vector<vector<int>> a(n);
	map<int, vector<int>> mexdomex;
	int maxk = 0;
	for (auto& x : a) {
		int k; cin >> k;
		ckmax(maxk, k);
		x.resize(k);
		vector<int> freq(k+5);
		for (auto& y : x) {
			cin >> y;
			if (y < k + 5) freq[y] = 1;
		}
		int m1 = -1, m2 = -1;
		for (int i = 0; i < k + 5; ++i) {
			if (freq[i] == 0) {
				if (m1 == -1) {
					m1 = i;
				} else {
					m2 = i;
					break;
				}
			}
		}
		mexdomex[m1].pb(m2);
	}
	// preciso fazer na mao ateh tipo maxk + 5, depois eh garantido q a resposta eh i
	maxk += 5;
	map<int, int> dp;
	int ans = max(0ll, (m-maxk)*(maxk+1+m)/2), bestdp = 0;
	for (int i = maxk; i >= 0; --i) {
		dp[i] = i;
		for (auto x : mexdomex[i]) ckmax(dp[i], dp[x]);
		if (sz(mexdomex[i]) > 1) ckmax(bestdp, dp[i]);
		if (sz(mexdomex[i]) != 0) ckmax(bestdp, i);
	}
	for (int i = 0; i <= min(m, maxk); ++i) ans += max(bestdp, dp[i]);
	cout << ans << endl;


}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
