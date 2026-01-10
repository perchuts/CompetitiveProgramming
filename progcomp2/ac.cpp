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
const int MAX = 505;
// Blossom 
//
// Matching maximo em grafo geral
//
// O(n^3)
// Se for bipartido, nao precisa da funcao
// 'contract', e roda em O(nm)

vector<int> g[MAX];
int match[MAX]; // match[i] = com quem i esta matchzado ou -1
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
	for (int i = 0; i < n; i++) if (bloss[base[i]]) {
		base[i] = l;
		if (!vis[i]) q.push(i);
		vis[i] = 1;
	}
}

int getpath(int s) {
	for (int i = 0; i < n; i++) base[i] = i, pai[i] = -1, vis[i] = 0;
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
	for (int i = 0; i < n; i++) if (match[i] == -1)
		for (int j : g[i]) if (match[j] == -1) {
			match[i] = j;
			match[j] = i;
			ans++;
			break;
		}
	for (int i = 0; i < n; i++) if (match[i] == -1) {
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

void solve() {
    int m; cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        g[u].pb(v), g[v].pb(u);
    }
    blossom();
    vector<ii> ans;
    for (int i = 0; i < n; ++i) {
        if (match[i] != -1 and i > match[i]) ans.pb({i, match[i]});
    }
    cout << sz(ans) << endl;
    for (auto [x, y] : ans) cout << x << ' ' << y << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
