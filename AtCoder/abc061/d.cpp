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
const int MAX = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
// Bellman-Ford
//
// Calcula a menor distancia
// entre a e todos os vertices e
// detecta ciclo negativo
// Retorna 1 se ha ciclo negativo
// Nao precisa representar o grafo,
// soh armazenar as arestas
//
// O(nm)

int n, m;
int d[MAX], mark[MAX];
const int INF = 1e18;
vector<pair<int, int>> ar; // vetor de arestas
vector<int> w;              // peso das arestas

bool bellman_ford(int a) {
	for (int i = 0; i < n; i++) d[i] = INF;
	d[a] = 0;

	for (int i = 0; i <= n; i++)
		for (int j = 0; j < m; j++) {
            if (!mark[ar[j].first] or !mark[ar[j].second]) continue;
            // se eu tenho um ciclo mas esse ciclo nao alcanca o vertice N, eu quero ignoralo
			if (d[ar[j].second] > d[ar[j].first] + w[j]) {
				if (i == n) return 1;
				d[ar[j].second] = d[ar[j].first] + w[j];
			}
		}

	return 0;
}

void solve(){
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int x, y, z; cin >> x >> y >> z;
        --x, --y;
        g[y].pb(x);
        ar.pb({x, y});
        w.pb(-z);
    }
    auto dfs = [&] (auto&& self, int u) -> void {
        mark[u] = 1;
        for (auto v : g[u]) {
            if (!mark[v]) self(self, v);
        }
    };
    dfs(dfs, n-1);
    if (bellman_ford(0)) cout << "inf" << endl;
    else cout << -d[n-1] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
