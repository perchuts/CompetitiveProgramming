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
	vector<vector<int>> g(n);
	for (int i = 0; i < n-1; ++i) {
		int u, v; cin >> u >> v;
		--u, --v;
		g[u].pb(v), g[v].pb(u);
	}
	vector<vector<int>> dp(n, vector<int>(3));	
	auto dfs = [&] (auto&& self, int u, int p) -> void {
		for (auto v : g[u]) {
			if (v == p) continue;
			self(self, v, u);
		}
		dp[u][0] = 1;
		dp[u][1] = dp[u][2] = 0;
		for (auto v : g[u]) {
			if (v == p) continue;
			dp[u][0] = dp[u][0] * (2*dp[v][1] + dp[v][2]) % mod;
		}
		for (auto escolhi : g[u]) {
			if (escolhi == p) continue;
			int cur = (dp[escolhi][1] + dp[escolhi][0]) % mod;
			for (auto nao : g[u]) {
				if (nao == escolhi or nao == p) continue;
				cur = cur * (2*dp[nao][1] + dp[nao][2]) % mod;
			}
			dp[u][1] = (dp[u][1] + cur) % mod;
		}
		for (auto e1 : g[u]) {
			if (e1 == p) continue;
			for (auto e2 : g[u]) {
				if (e2 == p or e2 <= e1) continue;
				int cur = (dp[e1][1] + dp[e1][0]) * (dp[e2][1] + dp[e2][0]) % mod;
				cur = (cur + cur) % mod;
				for (auto nao : g[u]) {
					if (nao == p or nao == e1 or nao == e2) continue;
					cur = cur * (2*dp[nao][1] + dp[nao][2]) % mod;
				}
				dp[u][2] = (dp[u][2] + cur) % mod;
			}
		}
	};
	for (int i = 0; i < n; ++i) {
		dfs(dfs, i, i);
		cout << (2*dp[i][1] + dp[i][2]) % mod << endl;
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
