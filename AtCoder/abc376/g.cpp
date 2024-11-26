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
	vector<int> p(n+1), par(n+1), ps(n+1), pval(n+1);
	int S = 0;
	for (int i = 1; i <= n; ++i) cin >> p[i];
	for (int i = 1; i <= n; ++i) cin >> pval[i], par[i] = i, ps[i] = 1, S += pval[i];
	p[0] = -1, ps[0] = 1;
	auto findp = [&] (auto&& self, int x) -> int {
		return par[x] = (x == par[x] ? x : self(self, par[x]));	
	};
	auto unite = [&] (int u, int v) {
		u = findp(findp, u), v = findp(findp, v);
		assert(u != v);
		par[u] = v, ps[v] += ps[u], pval[v] += pval[u];
	};
	set<pair<double, int>> s;
	auto inv = [&] (int b) {
		int ans = 1, e = mod-2;
		while (e) {
			if (e&1) ans = ans * b % mod;
			b = b * b % mod, e /= 2;
		}
		return ans;
	};
	int ans = 0;
	for (int i = 0; i <= n; ++i) s.insert({ -(double) pval[i], i});
	while (s.size() != 1) {
		auto it = begin(s);
		if (it->second == 0) it = next(it);
		int u = it->second, pai = findp(findp, p[u]);
		// juntar u com pai	
		ans += pval[u] * ps[pai];
		s.erase(it), s.erase({ -(double)pval[pai] / ps[pai], pai});
		unite(u, pai);
		s.insert({ -(double)pval[pai] / ps[pai], pai});
	}
	ans %= mod;
	cout << (ans * inv(S)) % mod << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
