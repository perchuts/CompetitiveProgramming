#include <bits/stdc++.h>
using namespace std;
#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

vector<int> pi(string s) {
	vector<int> p(s.size());
	for (int i = 1; i < s.size(); ++i) {
		int j = p[i-1];
		while (j and s[j] != s[i]) j = p[j-1];
		if (s[j] == s[i]) j++;
		p[i] = j;
	}
	return p;
}

int count_occ(string s, string p) {
	string ss = p;
	ss += "#";
	ss += s;
	auto pp = pi(ss);
	int ans = 0;
	for (int i = p.size()+1; i < ss.size(); ++i) if (pp[i] == p.size()) ans++;
	return ans;
}

vector<vector<int>> build_graph(vector<int> ps, int l, int n) {
	vector<vector<int>> g(n+l+2);
	for (int i = 0; i < l; ++i) {
		int j = ps[i]-1;
		if (j != -1) g[j].push_back(i);
		else g[n+l+1].push_back(i);
	}
	for (int i = 0; i < n; ++i) {
		int j = ps[l+1+i]-1;
		if (j != -1) g[j].push_back(i+l+1);
		else g[n+l+1].push_back(i+l+1);
	}
	return g;
}

vector<int> count_intersections(string s, string t, string p) {
	string sexo = t;
	sexo += "#";
	sexo += p;
	auto tp = pi(sexo); 	
	int n = s.size(), l = p.size();
	vector<int> suffix_t, mark_t(l+1);
	int cur = tp.back()-1;
	while (cur >= 0) {
		if (sexo[cur] == sexo.back()) suffix_t.push_back(cur+1), mark_t[cur+1] = 1;
		cur = tp[cur]-1;
	}
	sexo = p;
	sexo += "#";
	sexo += s;
	auto ps = pi(sexo);
	auto g = build_graph(ps, l, n);
	vector<int> resp(n);
	int faz_o_w = 0;
	auto dfs = [&] (auto&& self, int u) -> void {
		int type = ((u != l+n+1 && ps[u] != 0 && mark_t[l-ps[u]] == 1) ? 1 : 0);
		faz_o_w += type;
		for (auto v : g[u]) {
			self(self, v);
		}
		if (u != l+n+1 and u > l) resp[u-l-1] = faz_o_w;
		faz_o_w -= type;
	};
	dfs(dfs, n+l+1);
	return resp;
}

array<int, 4> compute_ans(vector<int> resp) {
	int n = resp.size();
	array<int, 4> ans = {0, 0, 0, 0};
	for (int i = 0; i < n; ++i) {
		if (resp[i] == ans[0]) {
			ans[1]++;
			ans[3] = i;
		} else if (resp[i] > ans[0]) {
			ans[0] = resp[i];
			ans[1] = 1;
			ans[2] = ans[3] = i;
		}
	}
	return ans;
}

vector<int> solve_easy(string s, string t, string p) {
	int n = s.size();
	vector<int> pref(n), suf(n);
	int internal = count_occ(t, p);
	string sexo = p;
	sexo += "#";
	sexo += s;
	auto ps = pi(sexo);
	int l = p.size();
	for (int i = (int) p.size()-1; i < n; ++i) {
		if (i) pref[i] = pref[i-1];
		pref[i] += (ps[i+l+1] == (int)p.size());
	}
	for (int i = n - 1; i >= 0; --i) {
		if (i != n-1) suf[i] = suf[i+1];
		suf[i] += (ps[i+l+1] == (int)p.size());
	}
	auto resp_left = count_intersections(s, t, p);
	reverse(begin(s), end(s)), reverse(begin(t), end(t)), reverse(begin(p), end(p));
	auto resp_right = count_intersections(s, t, p);
	reverse(begin(resp_right), end(resp_right));
	reverse(begin(s), end(s)), reverse(begin(t), end(t)), reverse(begin(p), end(p));
	vector<int> resp(n+1);
	for (int i = 0; i < n; ++i) {
		resp[i+1] = resp_left[i] + (i==n-1?0:resp_right[i+1]) + pref[i];
		if (i+(int)p.size() < n) resp[i+1] += suf[i+(int)p.size()];
	}
	sexo = t;
	sexo += s;
	resp[0] = count_occ(sexo, p) - internal;
	for (int i = 0; i <= n; ++i) resp[i] += internal;
	return resp;
}

vector<int> solve(string s, string t, string p) {
	int n = s.size(), l = p.size(), m = t.size();
	vector<int> resp = solve_easy(s, t, p);	
	string sexo = t; sexo += "#"; sexo += p;
	auto tp = pi(sexo);
	vector<int> pode(l);
	for (int i = m+1; i <= l+m; ++i) if (tp[i] == m) pode[i-2*m] = 1;
	sexo = p; sexo += "#"; sexo += s;

	auto ps = pi(sexo);
	vector<vector<vector<int>>> tree(2);
	tree[0] = build_graph(ps, l, n);

	reverse(begin(p), end(p)), reverse(begin(s), end(s));
	sexo = p; sexo += "#"; sexo += s;
	ps = pi(sexo); 
	tree[1] = build_graph(ps, l, n);

	vector<vector<pair<int, int>>> intr(2, vector<pair<int, int>>(l+n+2));

	int tt = 0;

	auto pre = [&] (auto&& self, int id, int u) -> void {
		intr[id][u].first = ++tt;
		for (auto v : tree[id][u]) self(self, id, v);	
		intr[id][u].second = tt;
	};

	pre(pre, 0, n+l+1); tt = 0; pre(pre, 1, n+l+1);

	vector<int> bit(l+n+2);

	auto insert = [&] (int x, int val) { while (x <= l+n+1) bit[x] += val, x += x & (-x); };

	auto query = [&] (int x) {
		int ans = 0;
		while (x) ans += bit[x], x -= x & (-x);
		return ans;
	};
	auto dfs = [&] (auto&& self, int u) {
		if (u > l and u != n+l+1) {
			int sym = n-1-(u-l);
			if (u != n+l) {
				resp[u-l] += query(intr[1][l+1+sym].first);
			}
			return;
		}
		int irmao = l-m-u-2;
		if (min(u, irmao) >= 0 and pode[u+1]) insert(intr[1][irmao].first, 1), insert(intr[1][irmao].second+1, -1);
		for (auto v : tree[0][u]) self(self, v);
		if (min(u, irmao) >= 0 and pode[u+1]) insert(intr[1][irmao].first, -1), insert(intr[1][irmao].second+1, 1);
	};

	dfs(dfs, n+l+1);

	return resp;
}

int32_t main() {
	fast_io;
	string s, t, p; cin >> s >> t >> p;
	array<int, 4> resp;
	resp = compute_ans(solve(s, t, p));
	cout << resp[0] << ' ' << resp[1] << ' ' << resp[2] << ' ' << resp[3] << endl;
}
