#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll
using namespace std;

using ll = long long;

const int MAX = 300;

vector<int> g[MAX];
int match[MAX];
int n, pai[MAX], base[MAX], vis[MAX];
queue<int> q;

void contract(int u, int v, bool first = 1) {
	static vector<bool> bloss;
	static int l;
	if (first) {
		bloss = vector<bool>(n, 0);
		vector<bool> teve(n, 0);
		int k = u; l = v;
		while (1) {
			teve[k = base[k]] = 1;
			if (match[k] == -1) break;
			k = pai[match[k]];
		}
		while (!teve[l = base[l]]) l = pai[match[l]];
	}
	while (base[u] != l) {
		bloss[base[u]] = bloss[base[match[u]]] = 1;
		pai[u] = v;
		v = match[u];
		u = pai[match[u]];
	}
	if (!first) return;
	contract(v, u, 0);
	for (int i = 0; i < n; ++i) if (bloss[base[i]]) {
		base[i] = l;
		if (!vis[i]) q.push(i);
		vis[i] = 1;
	}
}

int getpath(int s) {
	for (int i = 0; i < n; ++i) base[i] = i, pai[i] = -1, vis[i] = 0;
	vis[s] = 1; q = queue<int>(); q.push(s);
	while (q.size()) {
		int u = q.front(); q.pop();
		for (int i : g[u]) {
			if (base[i] == base[u] or match[u] == i) continue;
			if (i == s or (match[i] != -1 and pai[match[i]] != -1))
				contract(u, i);
			else if (pai[i] == -1) {
				pai[i] = u;
				if (match[i] == -1) return i;
				i = match[i];
				vis[i] = 1; q.push(i);
			}
		}
	}
	return -1;
}

int blossom() {
	int ans = 0;
	memset(match, -1, sizeof(match));
	for (int i = 0; i < n; ++i) if (match[i] == -1) 
		for (int j : g[i]) if (match[j] == -1) {
			match[i] = j;
			match[j] = i;
			ans++;
			break;
		}
	for (int i = 0; i < n; ++i) if (match[i] == -1) {
		int j = getpath(i);
		if (j == -1) continue;
		ans++;
		while (j != -1) {
			int p = pai[j], pp = match[p];
			match[p] = j;
			match[j] = p;
			j = pp;
		}
	}
	return ans;
}

int32_t main() {_ 
	int t; cin >> t;
	for (int zzz = 1; zzz <= t; ++zzz) {
		cout << "Case #" << zzz << ": ";
		int R, C; cin >> R >> C;
		vector<string> grid(R);
		for (auto& x : grid) cin >> x;
		n = R * C;
		for (int i = 0; i < n; ++i) g[i].clear();
		auto get = [&] (int i, int j) { return C * i + j; };
		int x, y;
		vector<int> delta = {-1, 0, 1};
		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < C; ++j) {
				if (grid[i][j] == '#') continue;
				int eu = get(i, j);
				for (auto dx : delta) {
					for (auto dy : delta) {
						if (dx == 0 and dy == 0) continue;
						int i2 = dx + i, j2 = dy + j;
						if (min(i2, j2) >= 0 and i2 < R and j2 < C and grid[i2][j2] != '#') g[eu].pb(get(i2, j2));
					}
				}
				if (grid[i][j] == 'K') x = i, y = j;
			}
		}
		int opt = blossom();
		int eu = get(x, y);
		for (auto i : g[eu]) {
			for (int j = 0; j < g[i].size(); ++j) {
				if (g[i][j] == eu) {
					g[i].erase(begin(g[i]) + j);
					break;
				}
			}
		}
		g[eu].clear();
		int opt2 = blossom();
		cout << "AB"[opt==opt2] << endl;
	}
}
