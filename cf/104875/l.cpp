#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
using namespace std;

using ll = long long;

const int mod = 998244353;
const int INF = 0x3f3f3f3f;

struct dinitz {
	const bool scaling = false;
	int lim;
	struct edge {
		int to, cap, rev, flow;
		bool res;
		edge(int to_, int cap_, int rev_, bool res_) 
			: to(to_), cap(cap_), rev(rev_), flow(0), res(res_) {}
	};

	vector<vector<edge>> g;
	vector<int> lev, beg;
	ll F;
	dinitz(int n) : g(n), F(0) {}

	void add(int a, int b, int c) {
		g[a].emplace_back(b, c, g[b].size(), false);
		g[b].emplace_back(a, 0, g[a].size() - 1, true);
	}

	bool bfs(int s, int t) {
		lev = vector<int>(g.size(), -1); lev[s] = 0;
		beg = vector<int>(g.size(), 0);
		queue<int> q; q.push(s);
		while (q.size()) {
			int u = q.front(); q.pop();
			for (auto & i : g[u]) {
				if (lev[i.to] != -1 or (i.flow == i.cap)) continue;
				if (scaling and i.cap - i.flow < lim) continue;
				lev[i.to] = lev[u] + 1;
				q.push(i.to);
			}
		}
		return lev[t] != -1;
	}
	int dfs(int v, int s, int f = INF) {
		if (!f or v == s) return f;
		for (int& i = beg[v]; i < g[v].size(); i++) {
			auto& e = g[v][i];
			if (lev[e.to] != lev[v] + 1) continue;
			int foi = dfs(e.to, s, min(f, e.cap - e.flow));
			if (!foi) continue;
			e.flow += foi, g[e.to][e.rev].flow -= foi;
			return foi;
		}
		return 0;
	}
	ll max_flow(int s, int t) {
		for (lim = scaling ? (1<<30) : 1; lim; lim /= 2)
			while (bfs(s, t)) while (int ff = dfs(s, t)) F += ff;
		return F;
	}
};

struct lb_max_flow : dinitz {
	vector<int> d;
	lb_max_flow(int n) : dinitz(n + 2), d(n, 0) {}
	void add(int a, int b, int l, int r) {
		d[a] -= l;
		d[b] += l;
		dinitz::add(a, b, r - l);
	}
	void add(int a, int b, int c) {
		dinitz::add(a, b, c);
	}
	bool has_circulation() {
		int n = d.size();

		ll cost = 0;
		for (int i = 0; i < n; i++) {
			if (d[i] > 0) {
				cost += d[i];
				dinitz::add(n, i, d[i]);
			} else if (d[i] < 0) {
				dinitz::add(i, n + 1, -d[i]);
			}
		}

		return (dinitz::max_flow(n, n + 1) == cost);
	}
	bool has_flow(int src, int snk) {
		dinitz::add(snk, src, INF);
		return has_circulation();
	}
	ll max_flow(int src, int snk) {
		if (!has_flow(src, snk)) return -1;
		dinitz::F = 0;
		return dinitz::max_flow(src, snk);
	}
};

int32_t main() {_
	int g, l;
	cin >> g >> l;
	--g;

	vector<string> guesses(g), feedback(g);
	for (int i = 0; i < g; i++) {
		cin >> guesses[i] >> feedback[i];
	}

	const int S = 26;
	vector<int> lb(S, 0), ub(S, l);

	for (int c = 0; c < S; c++) {
		for (int i = 0; i < g; i++) {
			int in = 0;
			int out = 0;
			for (int j = 0; j < l; j++) if (guesses[i][j] == 'a' + c) {
				if (feedback[i][j] == 'G' || feedback[i][j] == 'Y') in++;
				else out = 1;
			}
			if (in == 0 && out == 0) continue;
			lb[c] = max(lb[c], in);
			if (out) {
				lb[c] = max(lb[c], in);
				ub[c] = min(ub[c], in);
			}
		}
	}

	//for (int c = 0; c < S; c++) {
	//	if (val[c] == -1) continue;

	//	cout << char('a' + c) << ": ";

	//	if (black[c]) cout << "=";
	//	else cout << ">=";

	//	cout << val[c] << endl;
	//}
	
	vector<vector<int>> can(S, vector<int>(l, true));
	string ans(l, '.');
	for (int i = 0; i < g; i++) {
		for (int j = 0; j < l; j++) {
			if (feedback[i][j] == 'G') {
				ans[j] = guesses[i][j];
			} else {
				can[guesses[i][j] - 'a'][j] = false;
			}
		}
	}
	for (int j = 0; j < l; j++) if (ans[j] != '.') {
		lb[ans[j] - 'a'] = max(lb[ans[j] - 'a'] - 1, 0LL);
		ub[ans[j] - 'a'] = max(ub[ans[j] - 'a'] - 1, 0LL);
		//assert(ub[ans[j] - 'a'] >= 0);
		//assert(lb[ans[j] - 'a'] >= 0);
	}

	lb_max_flow st(S + l + 2);
	int src = S + l, snk = src + 1;

	for (int c = 0; c < S; c++) {
		st.add(src, c, lb[c], ub[c]);
		for (int j = 0; j < l; j++) if (can[c][j]) {
			st.add(c, S + j, 0, 1);
		}
	}
	for (int j = 0; j < l; j++) {
		if (ans[j] == '.') {
			//cout << j << " " << snk << endl;
			st.add(S + j, snk, 0, 1);
		}
	}
	//cout << st.max_flow(src, snk) << endl;
	st.max_flow(src, snk);

	for (int c = 0; c < S; c++) {
		for (auto e : st.g[c]) {
			if (e.flow == 1 && !e.res) {
				int j = e.to - S;
				ans[j] = 'a' + c;
			}
		}
	}

	cout << ans << endl;
}
