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

struct kuhn {
	int n, m; 
	vector<vector<int>> g;
	vector<int> vis, ma, mb;
	kuhn(int n_, int m_) : n(n_), m(m_), g(n), vis(n+m), ma(n, -1), mb(m, -1) {}
	int nao = -1;

	void add(int a, int b) { g[a].push_back(b); }

	bool dfs(int i) {
		vis[i] = 1;
		if (i == nao) return false;
		for (int j : g[i]) if (!vis[n+j]) {
			vis[n+j] = 1;
			if (mb[j] == -1 or dfs(mb[j])) {
				ma[i] = j, mb[j] = i;
				return true;
			}
		}
		return false;
	}
	int matching() {
		int ret = 0, aum = 1;
		for (auto& i : g) shuffle(all(i), rng);
		while (aum) {
			for (int j = 0; j < m; ++j) vis[n+j] = 0;
			aum = 0;
			for (int i = 0; i < n; ++i) 
				if (ma[i] == -1 and dfs(i)) ret++, aum = 1;
		}
		return ret;
	}
};

void solve(){
	int n, c; cin >> n >> c;
	string a, b; cin >> a >> b;
	vector<int> proibido(1<<n);
	for (int i = 0; i < c; ++i) {
		string s; cin >> s;
		int x = 0;
		for (int j = 0; j < n; ++j) if (s[j] == '.') x += (1 << j);
		proibido[x] = 1;
	}
	int src = 0;
	for (int j = 0; j < n; ++j) if (a[j] != b[j]) src += (1 << j);
	kuhn cu((1<<n), (1<<n));
	int paridade = __builtin_popcount(src) % 2;
	for (int i = 0; i < (1 << n); ++i) {
		for (int j = 0; j < n; ++j) {
			int w = i ^ (1 << j);
			if (w > i) continue;
			if (!proibido[i] and !proibido[w]) {
				if (__builtin_popcount(i) % 2 == paridade) cu.add(i, w);
				else cu.add(w, i);
			}
		}
	}
	int x = cu.matching();
	for (int i = 0; i < 2 * (1 << n); ++i) cu.vis[i] = 0;
	for (int i = 0; i < (1<<n); ++i) cu.ma[i] = -1;
	for (int i = 0; i < (1<<n); ++i) cu.mb[i] = -1;
	cu.nao = src;
	int y = cu.matching();
	if (x != y) cout << "Alice" << endl;
	else cout << "Bob" << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
