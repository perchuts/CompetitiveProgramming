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

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

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

void solve() {
    int n; cin >> n;
    bitset<10000005> b, prime;
    for (int i = 0; i < n; ++i) { int x; cin >> x; b[x] = 1; }
    vector<int> v;
    for (int i = 1; i <= 10000001; ++i) if (b[i] != b[i-1]) v.pb(i);
    prime[1] = 1;
    for (int i = 2; i <= 10000000; ++i) {
        if (!prime[i]) {
            for (int j = i * i; j <= 10000000; j += i) {
                prime[j] = 1;
            }
        }
    }
    vector<int> used(sz(v)), e, o;
    auto go = [&] () {
        kuhn cu(sz(e), sz(o));
        for (int i = 0; i < sz(e); ++i) {
            for (int j = 0; j < sz(o); ++j) {
                if (used[e[i]] or used[o[j]]) continue;
                if (!prime[abs(v[e[i]] - v[o[j]])]) {
                    cu.add(i, j);
                }
            }
        }
        return cu.matching();
    };
    for (int i = 0; i < sz(v); ++i) {
        if (v[i] & 1) o.pb(i);
        else e.pb(i);
    }
    int ans = sz(v) + 1;
    int m = go();
    ans = sz(v) - m + (sz(e) % 2 != m % 2);
    for (auto i : e) {
        for (auto j : o) {
            used[i] = used[j] = 1;
            m = go();
            if (m % 2 != sz(e) % 2) ckmin(ans, sz(v) + 1 - m);
            used[i] = used[j] = 0;
        }
    }
    cout << ans << endl;
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
