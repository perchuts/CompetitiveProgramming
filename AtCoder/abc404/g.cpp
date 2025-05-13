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
const int maxn = 2e5;

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

const int MAX = maxn;
const int INF = 1e18;
int n, m;
int d[MAX];
vector<pair<int, int>> ar; // vetor de arestas
vector<int> w;              // peso das arestas

bool bellman_ford(int a) {
	for (int i = 0; i < n; i++) d[i] = INF;
	d[a] = 0;

	for (int i = 0; i <= n; i++)
		for (int j = 0; j < m; j++) {
			if (d[ar[j].second] > d[ar[j].first] + w[j]) {
				if (i == n) return 1;

				d[ar[j].second] = d[ar[j].first] + w[j];
			}
		}

	return 0;
}
void solve(){
    int x; cin >> n >> x;
    n++;
    vector<int> l(x), r(x), s(x);
    for (int i = 0; i < x; ++i) cin >> l[i] >> r[i] >> s[i];
    auto add_constraint = [&] (int i, int j, int k) {
        // xi - xj <= k
        ar.pb({j, i});
        w.pb(k);
    };
    for (int i = 1; i < n; ++i) add_constraint(i-1, i, -1);
    for (int i = 0; i < x; ++i) {
        // r[i] - (l[i]-1) >= s[i]
        // r[i] - (l[i]-1) <= s[i]
        // (l[i]-1) - r[i] >= -s[i]
        add_constraint(r[i], l[i]-1, s[i]);
        add_constraint(l[i]-1, r[i], -s[i]);
    }
    for (int i = 0; i < n; ++i) ar.pb({n, i}), w.pb(0);
    m = sz(w), n++;
    if (bellman_ford(n-1)) {
        cout << -1 << endl;
        exit(0);
    }
    vector<int> a(n);
    int ss = 0;
    for (int i = 0; i < n; ++i) a[i] = d[i+1] - d[i], ss += a[i];
    cout << ss << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
