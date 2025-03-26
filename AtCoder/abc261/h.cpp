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

const int MAX = maxn;
int n;
vector<ii> g[MAX];
vector<ii> gi[MAX]; // grafo invertido
int vis[MAX];
stack<int> S;
int comp[MAX]; // componente conexo de cada vertice

void dfs(int k) {
	vis[k] = 1;
	for (int i = 0; i < (int) g[k].size(); i++)
		if (!vis[g[k][i].first]) dfs(g[k][i].first);

	S.push(k);
}

void scc(int k, int c) {
	vis[k] = 1;
	comp[k] = c;
	for (int i = 0; i < (int) gi[k].size(); i++)
		if (!vis[gi[k][i].first]) scc(gi[k][i].first, c);
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
    int m, X; cin >> n >> m >> X;
    --X;
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        --u, --v;
        g[u].pb({v, w});
        gi[v].pb({u, w});
    }
    kosaraju();
    const int INF = 9e18;
    vector<vector<int>> dp(n, vector<int>(2)), who(n);
    for (int i = 0; i < n; ++i) dp[i][0] = INF, dp[i][1] = -1;
    vector<int> out(n);
    for (int i = 0; i < n; ++i) {
        who[comp[i]].pb(i);
        for (auto [v, w] : g[i]) if (comp[v] != comp[i]) out[comp[i]] = 1;
    }
    vector<vector<int>> vis(n, vector<int>(2)), setado(n, vector<int>(2));
    priority_queue<iii, vector<iii>, greater<>> pq;
    for (int i = 0; i < n; ++i) {
        if (who[i].empty() or out[i]) continue;
        for (auto j : who[i]) {
            dp[j][0] = dp[j][1] = (sz(who[i]) == 1 ? 0 : INF);
            pq.push({dp[j][0], 0, j});
            pq.push({dp[j][1], 1, j});
        }
    }
    while (!pq.empty()) {
        auto [eu, j, i] = pq.top(); pq.pop();
        if (dp[i][j] != eu or vis[i][j]) continue;
        vis[i][j] = 1;
        for (auto [v, w] : gi[i]) {
            setado[v][j^1]++;
            if (j == 0) {
                ckmax(dp[v][j^1], min(INF, dp[i][j]+w));
                if (dp[v][j^1] == INF or setado[v][j^1] == sz(g[v])) pq.push({dp[v][j^1], j^1, v});
            }
            else {
                if (ckmin(dp[v][j^1], min(INF, dp[i][j]+w)) or setado[v][j^1] == sz(g[v])) pq.push({dp[v][j^1], j^1, v});
            }
        }
    }
    if (!vis[X][0] or dp[X][0] == INF) cout << "INFINITY" << endl;
    else cout << dp[X][0] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
