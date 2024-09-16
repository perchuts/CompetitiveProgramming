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
const int mod = 998244353;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

void solve(){
	int n; cin >> n;
	vector<int> a(n);
	int falta = 0;
	for (auto& x : a) {
		cin >> x;
		if (x != -1) x--;
		else falta++;
	}
	vector<int> vis(n, -1), qnt(n), cycle(n), dp(n+1), pot(n+1), st;
	dp[0] = pot[0] = 1;
	for (int i = 1; i <= n; ++i) pot[i] = pot[i-1] * n % mod;
	function<int(int,int)> dfs = [&] (int u, int comp) {
		st.pb(u);
		if (vis[u] != -1) return vis[u];
		vis[u] = comp;
		if (a[u] == -1) return -1ll;
		int k = dfs(a[u], comp);
		if (k != -1) vis[u] = k;
		return k;
	};
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		st.clear();
		int x = dfs(i, i);
		if (x == i) {
			reverse(all(st));
			for (int j = 1; j < sz(st); ++j) {
				qnt[i]++;
				if (st[j] == st[0]) break;
			}
			ans = (ans + pot[falta]) % mod;
			cycle[i] = 1;
		} else if (x != -1) qnt[x] += sz(st)-1;	
		else qnt[i] += sz(st);
	}
	for (int i = 0; i < n; ++i) {
		if (cycle[i] || qnt[i] == 0) continue;
		for (int j = n; j >= 0; --j) {
			dp[j] = dp[j] * n % mod;
			if (j) dp[j] = (dp[j] + dp[j-1] * max(1ll,j-1) % mod * qnt[i]) % mod;
		}	
	}	
	for (int i = 1; i <= n; ++i) ans = (ans + dp[i]) % mod;	
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
