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
// Kosaraju
//
// O(n + m)

const int MAX = 2010;
int n, m;
vector<int> g[MAX];
vector<int> gi[MAX]; // grafo invertido
int vis[MAX];
stack<int> S;
int comp[MAX]; // componente conexo de cada vertice

void dfs(int k) {
	vis[k] = 1;
	for (int i = 0; i < (int) g[k].size(); i++)
		if (!vis[g[k][i]]) dfs(g[k][i]);

	S.push(k);
}

void scc(int k, int c) {
	vis[k] = 1;
	comp[k] = c;
	for (int i = 0; i < (int) gi[k].size(); i++)
		if (!vis[gi[k][i]]) scc(gi[k][i], c);
}

void kosaraju() {
	for (int i = 0; i < n; i++) vis[i] = 0;
	for (int i = 0; i < n; i++) if (!vis[i]) dfs(i);

	for (int i = 0; i < n; i++) vis[i] = 0;
	while (S.size()) {
		int u = S.top();
		S.pop();
		if (!vis[u]) scc(u, u);
	}
}
void solve(){
    cin >> n >> m;
    vector<array<int, 4>> a(m);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 4; ++j) cin >> a[i][j], --a[i][j];
        if (a[i][0] == a[i][2] and a[i][1] >= a[i][3]) {
            cout << "No" << endl;
            exit(0);
        }
    }
    vector<int> par(n), lvl(n); iota(all(par), 0);
    auto findp = [&] (auto&& self, int u) -> int { return par[u] = (par[u] == u ? u : self(self, par[u])); };
    auto merge = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) return;
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        if (lvl[u] == lvl[v]) lvl[u]++;
    };
    while (true) {
        for (int i = 0; i < n; ++i) g[i].clear(), gi[i].clear();
        for (int i = 0; i < m; ++i) {
            int u = findp(findp, a[i][0]);
            int v = findp(findp, a[i][2]);
            if (u != v) g[u].pb(v), gi[v].pb(u);
        }
        kosaraju();
        vector<array<int, 4>> na;
        for (int i = 0; i < n; ++i) merge(i, comp[i]);
        bool bad = 0;
        for (int i = 0; i < m; ++i) {
            if (findp(findp, a[i][0]) == findp(findp, a[i][2])) {
                if (a[i][3] == a[i][2]) {
                    cout << "No" << endl;
                    exit(0);
                }
                if (a[i][0] < a[i][1]) na.pb({a[i][0]+1, a[i][1], a[i][2]+1, a[i][3]}), bad = 1;
            } else na.pb(a[i]);
        }
        if (bad == 0) {
            cout << "Yes" << endl;
            exit(0);
        }
        swap(a, na);
        m = sz(a);
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
