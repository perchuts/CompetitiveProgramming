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

namespace sparse {
	int m[20][maxn], n;
	void build(int n2, vector<int>& v) {
		n = n2;
		for (int i = 0; i < n; i++) m[0][i] = v[i];
		for (int j = 1; (1<<j) <= n; j++) for (int i = 0; i+(1<<j) <= n; i++)
			m[j][i] = max(m[j-1][i], m[j-1][i+(1<<(j-1))]);
	}
	int query(int a, int b) {
		if (a > b) return 1;
		int j = __builtin_clz(1) - __builtin_clz(b-a+1);
		return max(m[j][a], m[j][b-(1<<j)+1]);
	}
};

void solve(){
	int n; cin >> n;
	vector<int> a(n), b(n);
	for (auto& x : a) cin >> x;
	for (auto& x : b) cin >> x;
	sparse::build(n, a);
	vector<int> lx(n), rx(n);
	vector<vector<int>> g(n+1);
	stack<ii> st;
	st.push({0, -1});
	vector<int> par(n), lvl(n), mxval(n);
	iota(all(par), 0);
	auto findp = [&] (auto&& self, int u) -> int {
		if (par[u] == u) return u;
		return par[u] = self(self, par[u]);
	};
	auto merge = [&] (int u, int v) {
		u = findp(findp, u), v = findp(findp, v);
		if (u == v) return;
		if (lvl[u] < lvl[v]) swap(u, v);
		par[v] = u;
		ckmax(mxval[u], mxval[v]);
		if (lvl[u] == lvl[v]) lvl[u]++;
	};
	for (int i = 0; i < n; ++i) {
		mxval[i] = a[i];
		while (st.top().first >= b[i]) {
			if (st.top().first == b[i]) merge(st.top().second, i);
			st.pop();
		}
		lx[i] = st.top().second;
		st.push({b[i], i});
	}
	while (!st.empty()) st.pop();
	st.push({0, n});
	for (int i = n-1; i >= 0; --i) {
		while (st.top().first >= b[i]) st.pop();
		rx[i] = st.top().second;
		st.push({b[i], i});
	}
	int root = n;
	for (int i = 0; i < n; ++i) {
		if (findp(findp, i) != i) continue;
		// os filhos de um cara sao disjuntos!
		if (lx[i] == -1 and rx[i] == n) {
			root = i;
			continue;
		}
		if (lx[i] == -1) g[findp(findp, rx[i])].pb(i);
		else if (rx[i] == n) g[findp(findp, lx[i])].pb(i);
		else {
			if (b[lx[i]] > b[rx[i]]) g[findp(findp, lx[i])].pb(i);
			else g[findp(findp, rx[i])].pb(i);
		}
	}
	int lim = 62;
	vector<vector<int>> dp(n, vector<int>(lim));
	vector<int> tam(n);
	for (int i = 0; i < n; ++i) {
		int cur = 1e18;
		while (cur > 1) tam[i]++, cur = (cur + b[i] - 1) / b[i];
		tam[i]++;
	}
	auto dfs = [&] (auto&& self, int u) -> void {
		int myl = lx[u]+1, myr = rx[u]-1; 
		for (auto v : g[u]) {
			//cout << u << " -> " << v << endl;
			self(self, v);
			vector<int> ndp(tam[u], 1e18);
			for (int i = 0; i < tam[u]; ++i) {
				for (int j = 0; j < tam[v] and i + j < tam[u]; ++j) {
					ckmin(ndp[i+j], max(dp[u][i], dp[v][j]));	
				}
			}
			dp[u] = ndp;
		}
		if (u == 1) {
			//cout << "Aqui: ";
			//for (int j = 0; j < 4; ++j) //cout << dp[u][j] << " ";
			//cout << endl;
		}
		dp[u][0] = sparse::query(myl, myr);
		for (int i = 1; i < tam[u]; ++i) {
			ckmax(dp[u][i], mxval[u]);
			int val = (dp[u][i-1] + b[u] - 1) / b[u];
			if (dp[u][i] == 0) dp[u][i] = val;
			else ckmin(dp[u][i], val);
		}
	};
	dfs(dfs, root);
	cout.flush();
	for (int i = 0; i < lim; ++i) {
		if (dp[root][i] == 1) {
			cout << i << endl;
			return;
		}
	}
	assert(false);
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}

