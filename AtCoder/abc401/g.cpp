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
// Kuhn
//
// Computa matching maximo em grafo bipartido
// 'n' e 'm' sao quantos vertices tem em cada particao
// chamar add(i, j) para add aresta entre o cara i
// da particao A, e o cara j da particao B
// (entao i < n, j < m)
// Para recuperar o matching, basta olhar 'ma' e 'mb'
// 'recover' recupera o min vertex cover como um par de
// {caras da particao A, caras da particao B}
//
// O(|V| * |E|)
// Na pratica, parece rodar tao rapido quanto o Dinitz

struct kuhn {
	int n, m;
	vector<vector<int>> g;
	vector<int> vis, ma, mb;

	kuhn(int n_, int m_) : n(n_), m(m_), g(n),
		vis(n+m), ma(n, -1), mb(m, -1) {}

	void add(int a, int b) { g[a].push_back(b); }

	bool dfs(int i) {
		vis[i] = 1;
		for (int j : g[i]) if (!vis[n+j]) {
			vis[n+j] = 1;
			if (mb[j] == -1 or dfs(mb[j])) {
				ma[i] = j, mb[j] = i;
				return true;
			}
		}
		return false;
	}
	int matching() {
		int ret = 0, aum = 1;
		for (auto& i : g) shuffle(i.begin(), i.end(), rng);
		while (aum) {
			for (int j = 0; j < m; j++) vis[n+j] = 0;
			aum = 0;
			for (int i = 0; i < n; i++)
				if (ma[i] == -1 and dfs(i)) ret++, aum = 1;
		}
		return ret;
	}
};

void solve(){
    int n; cin >> n;
    vector<ii> src(n), sink(n);
    for (auto& [x, y] : src) cin >> x >> y;
    for (auto& [x, y] : sink) cin >> x >> y;
    auto get = [&] (double x) {
        kuhn cu(n, n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                double d = hypot(src[i].first-sink[j].first, src[i].second-sink[j].second);
                if (d <= x) cu.add(i, j);
            }
        }
        return cu.matching();
    };
    double l = 0, r = 3e18;
    for (int i = 0; i < 100; ++i) {
        double md = (l+r)/2;
        if (get(md) == n) r = md;
        else l = md;
    }
    cout << fixed << setprecision(10) << l << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
