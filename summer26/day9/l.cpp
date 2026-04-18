#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll
using namespace std;

using ll = long long;

int n;

const int MAX = 3e5 + 100;

namespace d_tree {
	vector<int> g[MAX];
	vector<int> tree[MAX];
	int dfs_l[MAX], dfs_r[MAX];

	vector<int> rg[MAX], bucket[MAX];
	int idom[MAX], sdom[MAX], prv[MAX], pre[MAX];
	int ancestor[MAX], label[MAX];
	vector<int> preorder;

	void dfs(int v) {
		static int t = 0;
		pre[v] = ++t;
		sdom[v] = label[v] = v;
		preorder.push_back(v);
		for (int nxt : g[v]) {
			if (sdom[nxt] == -1) {
				prv[nxt] = v;
				dfs(nxt);
			}	
			rg[nxt].push_back(v);
		}
	}

	int eval(int v) {
		if (ancestor[v] == -1) return v;
		if (ancestor[ancestor[v]] == -1) return label[v];
		int u = eval(ancestor[v]);
		if (pre[sdom[u]] < pre[sdom[label[v]]]) label[v] = u;
		ancestor[v] = ancestor[u];
		return label[v];
	}
	void dfs2(int v) {
		static int t = 0;
		dfs_l[v] = t++;
		for (int nxt : tree[v]) dfs2(nxt);
		dfs_r[v] = t++;
	}
	void build(int s) {
		for (int i = 0; i < n; ++i) {
			sdom[i] = pre[i] = ancestor[i] = -1;
			rg[i].clear();
			tree[i].clear();
			bucket[i].clear();
		}
		preorder.clear();
		dfs(s);
		if (preorder.size() == 1) return;
		for (int i = int(preorder.size()) - 1; i >= 1; --i) {
			int w = preorder[i];
			for (int v : rg[w]) {
				int u = eval(v);
				if (pre[sdom[u]] < pre[sdom[w]]) sdom[w] = sdom[u];
			}
			bucket[sdom[w]].push_back(w);
			ancestor[w] = prv[w];
			for (int v : bucket[prv[w]]) {
				int u = eval(v);
				idom[v] = (u == v) ? sdom[v] : u;
			}
			bucket[prv[w]].clear();
		}
		for (int i = 1; i < preorder.size(); ++i) {
			int w = preorder[i];
			if (idom[w] != sdom[w]) idom[w] = idom[idom[w]];
			tree[idom[w]].push_back(w);
		}
		idom[s] = sdom[s] = -1;
		dfs2(s);
	}

	bool dominates(int u, int v) {
		if (pre[v] == -1) return 1;
		return (dfs_l[u] <= dfs_l[v] && dfs_r[v] <= dfs_r[u]);
	}

}


int32_t main() {_ 
	int m; cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int u, v; cin >> u >> v; --u, --v;
		d_tree::g[u].pb(v);
	}
	d_tree::build(0);
	vector<int> ans;
	for (int i = 0; i < n; ++i) {
		if (d_tree::dominates(i, n-1)) ans.push_back(i);
	}
	cout << ans.size() << endl;
	for (auto x : ans) cout << x + 1 << " ";
	cout << endl;
}
