#include <bits/stdc++.h>
using namespace std;
#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define gato
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

int rnd(int l, int r) {
	return l + rand() % (r-l+1);
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
	//cout << "s: " << s << endl;
	//cout << "t: " << t << endl;
	//cout << "p: " << p << endl;
	string sexo = t;
	sexo += "#";
	sexo += p;
	auto tp = pi(sexo); 	
	//cout << sexo << endl;
	//cout << "tp: ";
	//for (auto x : tp) cout << x << ' ';
	//cout << endl;
	// sufixos de P que encaixam no t
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
	//cout << sexo << endl;
	//cout << "ps: ";
	//for (auto x : ps) cout << x << ' ';
	//cout << endl;
	//cout << "mark_t: ";
	//for (auto x : mark_t) cout << x << ' ';
	//cout << endl;
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
	//cout << "resp: ";
	//for (auto x : resp) cout << x << ' ';
	//cout << endl;
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
	// sufixo de T eh prefixo de P
	auto resp_left = count_intersections(s, t, p);
	reverse(begin(s), end(s)), reverse(begin(t), end(t)), reverse(begin(p), end(p));
	auto resp_right = count_intersections(s, t, p);
	reverse(begin(resp_right), end(resp_right));
	reverse(begin(s), end(s)), reverse(begin(t), end(t)), reverse(begin(p), end(p));
	vector<int> resp(n+1);
	//cout << "resp_left: ";
	//for (auto x : resp_left) cout << x << ' ';
	//cout << endl;
	//cout << "resp_right: ";
	//for (auto x : resp_right) cout << x << ' ';
	//cout << endl;
//cout << "pref: ";
	//for (auto x : pref) cout << x << ' ';
	//cout << endl;
	//cout << "suf: ";
	//for (auto x : suf) cout << x << ' ';
	//cout << endl;
	for (int i = 0; i < n; ++i) {
		resp[i+1] = resp_left[i] + (i==n-1?0:resp_right[i+1]) + pref[i];
		if (i+(int)p.size() < n) resp[i+1] += suf[i+(int)p.size()];
	}
	sexo = t;
	sexo += s;
	resp[0] = count_occ(sexo, p) - internal;
	for (int i = 0; i <= n; ++i) resp[i] += internal;
	//cout << "resp: ";
	//for (auto x : resp) cout << x << ' ';
	//cout << endl;
	return resp;
}

vector<int> solve_hard(string s, string t, string p) {
	int n = s.size(), l = p.size(), m = t.size();
	vector<int> resp = solve_easy(s, t, p);	
	//cout << "resp before: ";
	//for (auto x : resp) cout << x << ' ';
	//cout << endl;

	string sexo = t; sexo += "#"; sexo += p;
	auto tp = pi(sexo);
	vector<int> pode(l);
	// pode[i] guarda se da pra ter um prefixo de tamanho i antes de colocar o t
	for (int i = m+1; i <= l+m; ++i) if (tp[i] == m) pode[i-2*m] = 1;
	//cout << sexo << endl;
	//cout << "tp: ";
	//for (auto x : tp) cout << x << ' ';
	//cout << endl;
	sexo = p; sexo += "#"; sexo += s;

	auto ps = pi(sexo);
	//cout << sexo << endl;
	//cout << "ps: ";
	//for (auto x : ps) cout << x << ' ';
	//cout << endl;
	vector<vector<vector<int>>> tree(2);
	tree[0] = build_graph(ps, l, n);

	reverse(begin(p), end(p)), reverse(begin(s), end(s));
	sexo = p; sexo += "#"; sexo += s;
	ps = pi(sexo); 
	tree[1] = build_graph(ps, l, n);
	//cout << sexo << endl;
	//cout << "ps: ";
	//for (auto x : ps) cout << x << ' ';
	//cout << endl;
	//cout << "pode: ";
	//for (auto x : pode) cout << x << ' ';
	//cout << endl;

	vector<vector<pair<int, int>>> intr(2, vector<pair<int, int>>(l+n+2));

	int tt = 0;

	auto pre = [&] (auto&& self, int id, int u) -> void {
		intr[id][u].first = ++tt;
		for (auto v : tree[id][u]) {
			//cout << id << ' ' << u << " -> " << v << endl;
			self(self, id, v);	
		}
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
		//cout << "vertice: " << u << endl;
		if (u > l and u != n+l+1) {
			int sym = n-1-(u-l);
			//cout << "pares: " << u-l-1 << ' ' << sym+l+1 << endl;
			//cout << "query " << intr[1][l+1+sym].first << endl;
			if (u != n+l) {
				resp[u-l] += query(intr[1][l+1+sym].first);
			}
			return;
		}
		// preciso ter que irmao + u == l-m
		int irmao = l-m-u-2;
		//cout << "irmaozinhos: ";
		//cout << u << ' ' << irmao << endl;
		if (min(u, irmao) >= 0 and pode[u+1]) {
			//cout << "inserindo no range: " << intr[1][irmao].first << ' ' << intr[1][irmao].second << endl;
			insert(intr[1][irmao].first, 1), insert(intr[1][irmao].second+1, -1);
		}
		for (auto v : tree[0][u]) self(self, v);
		if (min(u, irmao) >= 0 and pode[u+1]) {
			//cout << "retirando no range: " << intr[1][irmao].first << ' ' << intr[1][irmao].second << endl;
			insert(intr[1][irmao].first, -1), insert(intr[1][irmao].second+1, 1);
		}
	};

	dfs(dfs, n+l+1);
	//cout << "resp: ";
	//for (auto x : resp) cout << x << ' ';
	//cout << endl;

	return resp;
}

vector<int> brute(string s, string t, string p) {
	int n = s.size();
	vector<int> answer(n+1);
	for (int i = 0; i < n; ++i) {
		string sexo;
		for (int j = 0; j < i; ++j) sexo += s[j];
		sexo += t;
		for (int j = i; j < n; ++j) sexo += s[j];
		answer[i] = count_occ(sexo, p);	
	}
	string sexo = s;
	sexo += t;
	answer.back() = count_occ(sexo, p);
	return answer;
}

int32_t main() {
#ifndef gato
	fast_io;
	string s, t, p; cin >> s >> t >> p;
	array<int, 4> resp;
	if (p.size() <= t.size()) resp = compute_ans(solve_easy(s, t, p));
	else resp = compute_ans(solve_hard(s, t, p));
	cout << resp[0] << ' ' << resp[1] << ' ' << resp[2] << ' ' << resp[3] << endl;
#else
	int T = 1, lim = 50, let = 4;
	while (true) {
		srand(T++);
		int n = rnd(1, lim), m = rnd(1, lim), l = rnd(1, lim);
		string s, t, p;
		for (int i = 0; i < n; ++i) s.push_back(char('a'+rnd(0, let)));
		for (int i = 0; i < m; ++i) t.push_back(char('a'+rnd(0, let)));
		for (int i = 0; i < l; ++i) p.push_back(char('a'+rnd(0, let)));
		array<int, 4> my;
		my = compute_ans(solve_hard(s, t, p));
		array<int, 4> sol = compute_ans(brute(s, t, p));
		if (my != sol) {
			cout << "Wrong answer on test " << T << endl;
			cout << s << endl << t << endl << p << endl;
			cout << "Your output: " << my[0] << ' ' << my[1] << ' ' << my[2] << ' ' << my[3] << endl;
			cout << "Answer: " << sol[0] << ' ' << sol[1] << ' ' << sol[2] << ' ' << sol[3] << endl;
			exit(0);
		}
		cout << "Accepted on test " << T++ << endl;
	}
#endif
}

