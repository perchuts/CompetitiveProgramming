#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T>
	using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;
#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;
	int k; cin >> k;
	ord_set<pair<int, int>> s;
	vector<int> a(k);
	for (auto& x : a) cin >> x;
	for (int i = 0; i < k; ++i) s.insert({a[i], i});
	int n; cin >> n;
	vector<array<int, 2>> restr(n);
	for (auto& x : restr) cin >> x[0] >> x[1];
	int m; cin >> m;
	vector<vector<pair<int, int>>> g(n);
	for (int i = 0; i < m; ++i) {
		int u, v; cin >> u >> v;
		int qnt = k - s.order_of_key({restr[u][0]-1, k});
		g[u].push_back({v, qnt*restr[u][1]}); 
		//cout << u << "->" << v << " " << qnt*restr[u][1] << endl;
		qnt = k - s.order_of_key({restr[v][0]-1, k});
		//cout << v << "->" << u << " " << qnt*restr[v][1] << endl;
		g[v].push_back({u, qnt*restr[v][1]}); 
	}
	int l = 1, r = min(restr[n-1][1] * (k-s.order_of_key({restr[n-1][0]-1, k})), restr[0][1] * (k-s.order_of_key({restr[0][0]-1, k}))), ans = 0;
	auto possible = [&] (int x) {
		vector<int> vis(n);
		queue<int> q;
		q.push(0), vis[0] = 1;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			if (u == n-1) return true;
			for (auto [v, w] : g[u]) {
				if (vis[v] or w < x) continue;
				vis[v] = 1;
				q.push(v);
			}
		}
		return false;
	};
	while (l <= r) {
		int md = l + (r-l+1)/2;
		if (possible(md)) ans = md, l = md+1;
		else r = md-1;
	}
	cout << ans << endl;
}
