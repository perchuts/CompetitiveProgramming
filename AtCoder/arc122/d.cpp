#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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
const int MAX = 2e5 + 10;
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
int solve(vector<int> a) {
    int ans = 0, help = 1;
    vector<array<int, 3>> adj(32*n);
	vector<int> val(32*n);
    for (int i = 0; i < n; ++i) {
        int cur = 0;
        for (int j = 29; ~j; --j) {
            int want = a[i] >> j & 1;
            if (adj[cur][want] == 0) adj[cur][want] = help++, val[help-1] = val[cur] + (want << j);
            cur = adj[cur][want], adj[cur][2]++;
        }
    }
    for (int bit = 29; ~bit; --bit) {
        ans += (1 << bit);
        auto go = [&] (auto&& self, int u, int v, int h) -> bool {
            if (min(u, v) == 0 or h == -1) return false;
            if (ans >> h & 1) {
                if (min(adj[u][0], adj[v][0]) or min(adj[u][1], adj[v][1])) return true;
                bool nice = 0;
                nice |= self(self, adj[u][0], adj[v][1], h-1);
                nice |= self(self, adj[u][1], adj[v][0], h-1);
				return nice;
            } 
            bool nice = 0;
            nice |= self(self, adj[u][0], adj[v][0], h-1);
            nice |= self(self, adj[u][1], adj[v][1], h-1);
            return nice;
        };
        auto solve = [&] (auto&& self, int cur, int h) -> bool {
            if (ans >> h & 1) {
                if (adj[adj[cur][1]][2] % 2 == 0) return true;
                return go(go, adj[cur][0], adj[cur][1], h-1);
            } 
            if (adj[adj[cur][1]][2] & 1) return false; 
            bool good = true;
            if (adj[cur][0]) good &= self(self, adj[cur][0], h-1);
            if (adj[cur][1]) good &= self(self, adj[cur][1], h-1);
            return good;
        };
        if (solve(solve, 0, 29)) ans -= (1 << bit);
    }
    return ans;
}

int brute(vector<int> a) {
    int ans = 0;
    for (int bit = 29; ~bit; --bit) {
        ans += (1 << bit);
        for (int i = 0; i < n; ++i) g[i].clear();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if ((a[i] ^ a[j]) < ans) g[i].pb(j), g[j].pb(i);
            }
        }
        if (blossom() == n/2) ans -= (1 << bit);
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    cin >> n;
    n *= 2;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    cout << solve(a) << endl;
#else
    int t = 1;
    while (true) {
        n = rnd(2, 40);
        int bits = 30;
        n *= 2;
        vector<int> a(n);
        for (auto& x : a) x = rnd(0, (1 << bits) - 1);
        int my = solve(a), ans = brute(a);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n/2 << endl;
            for (auto x : a) cout << x << " ";
            cout << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
