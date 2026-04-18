#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll

using namespace std;

using ll = long long;

struct node {
	pair<ll, int> val;
	ll lazy;
	node *l, *r;
	node () {}
	node(pair<int, int> v) : val(v), lazy(0), l(NULL), r(NULL) {}

	void prop() {
		val.first += lazy;
		if (l) l->lazy += lazy;
		if (r) r->lazy += lazy;
		lazy = 0;
	}
};

void merge(node*& a, node* b) {
	if (!a) swap(a, b);
	if (!b) return;
	a->prop(), b->prop();
	if (a->val > b->val) swap(a, b);
	merge(rand()%2 ? a->l : a->r, b);
}

pair<ll, int> pop(node*& R) {
	R->prop();
	auto ret = R->val;
	node* tmp = R;
	merge(R->l, R->r);
	R = R->l;
	if (R) R->lazy -= ret.first;
	delete tmp;
	return ret;
}

void apaga(node* R) { if (R) apaga(R->l), apaga(R->r), delete R; }

const int LINF = 1e18;

pair<ll, vector<pair<int, int>>> dmst(int n, int r, vector<pair<pair<int, int>, int>>& ar) {
	vector<int> p(n); iota(begin(p), end(p), 0);
	function<int(int)> find = [&] (int k) { return p[k] == k ? k : p[k] = find(p[k]); };
	vector<node*> h(n);
	for (auto e : ar) merge(h[e.first.second], new node({e.second, e.first.first}));
	vector<int> pai(n, -1), path(n), pai_real(n);
	pai[r] = r;
	ll ans = 0;
	for (int i = 0; i < n; ++i) {
		int u = i, at = 0;
		while (pai[u] == -1) {
			if (!h[u]) {
				for (auto i : h) apaga(i);
				return {LINF, {}};
			}
			path[at++] = u, pai[u] = i;
			auto [mi, v] = pop(h[u]);
			pai_real[u] = v;
			ans += mi;

			if (pai[u = find(v)] == i) {
				while (find(v = path[--at]) != u) 
					merge(h[u], h[v]), h[v] = NULL, p[find(v)] = u;
				pai[u] = -1;
			}
		}
	}
	vector<pair<int, int>> edges;
	for (int i = 0; i < n; ++i) {
		if (i == r) continue;
		edges.push_back({pai_real[i], i});
	}
	for (auto i : h) apaga(i);
	return {ans, edges};
}

int32_t main() {_
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, m; cin >> n >> m;
	vector<pair<pair<int, int>, int>> ar(m);
	map<pair<int, int>, int> edg;
	for (int i = 0; i < m; ++i) {
		int u, v, w; cin >> u >> v >> w; --u, --v;
		edg[{u, v}] = i;
		ar[i] = {{u, v}, w};
	}
	auto [cost, used] = dmst(n, 0, ar);
	if (cost == LINF) {
		cout << -1 << endl;
		exit(0);
	}
	vector<int> ids;
	for (auto [u, v] : used) {
		if (ar[edg[{u, v}]].second != 0) ids.push_back(edg[{u, v}]);
	}
	cout << ids.size() << endl;
	for (auto x : ids) cout << x + 1 << " ";
	cout << endl;
}

