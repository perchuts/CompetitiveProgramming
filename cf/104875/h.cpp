#include <bits/stdc++.h>
#define int long long
#define sz(x) (int) x.size()
#define pb push_back
#define fast ios_base::sync_with_stdio(0); cin.tie(0);
using namespace std;

using ll = long long;

const int mod = 998244353;
const int inf = 2e9 + 100;
const int maxn = 2e5+10;

using pii = pair<int, int>;

struct Seg {
	int n;
	vector<pii> tree;
	Seg(int _n = 0) : n(_n), tree(2 * n, {-1, -1}) {}
	void update(int i, int v) { // a[i] = v
		i += n;
		tree[i] = {v, i - n};
		for (; i; i /= 2) {
			tree[i/2] = max(tree[i], tree[i^1]);
		}
	}
	pii query(int l, int r) { // query(l, r)
		pii ans = {-1, -1};
		for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
			if (r & 1) ans = max(ans, tree[--r]);
			if (l & 1) ans = max(ans, tree[l++]);
		}
		return ans;
	}
};

vector<int> g[maxn];

int lx[maxn], rx[maxn], dep[maxn], par[maxn], t, child[maxn], inv[maxn];

void pre(int u, int p) {
	lx[u] = ++t, dep[u] = dep[p]+1, par[u] = p, child[p]++;
	inv[t] = u;
	for (auto v : g[u]) {
		if (v == p) continue;
		pre(v, u);
	}
	rx[u] = t;
}

int ans = 0;

void dfs(int u, int p, Seg& st) {
	int esq = 0, dir = 0, v1 = -1, v2 = -1;
	for (auto v : g[u]) {
		if (v == p) continue;
		dfs(v, u, st);
		if (v1 == -1) esq = st.query(lx[v], rx[v]).first - dep[u], v1 = v;
		else dir = st.query(lx[v], rx[v]).first - dep[u], v2 = v;
	}
	int chosen = -1;
	if (esq + 1 < dir) {
		assert(v2 != -1);
		chosen = v2;
	} else if (dir + 1 < esq) {
		assert(v1 != -1);
		chosen = v1;
	}
	if (chosen != -1) {
		int target = min(esq, dir) + 1;
		while (true) {
			auto [dd, ind] = st.query(lx[chosen], rx[chosen]);
			dd -= dep[u];
			if (dd == target) break;
			int quem = inv[ind];
			assert(quem != 0);
			ans++;
			st.update(ind, 0);
			child[par[quem]]--;
			if (child[par[quem]] == 0) {
				st.update(lx[par[quem]], dep[par[quem]]);
			}
		}
	}
}

int32_t main() {fast
	int n; cin >> n;
	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	pre(1, 0);
	Seg st(t+10);

	for (int i = 1; i <= n; ++i) if (child[i] == 0) st.update(lx[i], dep[i]);

	dfs(1, 1, st);

	cout << ans << endl;
}
