#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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

double rnd_d(double l, double r) {
      uniform_real_distribution<double> uid(l, r);
      return uid(rng);
}


const double a = 0.99999;

double last = 1e9;
// double eps = 1e-8;

double temperature(int tries, int limit) { return last *= a; }


bool change(int x, int y, double t) {
      if (y > x) return true;
      double p = exp((y - x) / t), k = rnd_d(0, 1);
      return p >= k;
}

bool adj[100][100];

void solve() {
	auto start = chrono::steady_clock::now();
	auto get_time = [&]() {
		auto curr = chrono::steady_clock::now();
		return int32_t(chrono::duration_cast<chrono::milliseconds>(curr - start).count());
	};
    int n, m, l, d, e; cin >> n >> m >> l >> d >> e;
    vector<vector<int>> g(n), g2(n);
    const int n_facts = 100;
    vector<vector<int>> onde(n_facts);
    struct memory {
        int li, ri;
        vector<int> f;
		bitset<100> mask;
        memory (int lx, int rx, int tam) {
            li = lx, ri = rx;
            f = vector<int>(tam);
            for (auto& x : f) cin >> x, --x, mask[x] = 1;
        };
        memory () {}
    };
    vector<memory> mm(n);
    for (int i = 0; i < n; ++i) {
        int a, b, c; cin >> a >> b >> c;
        mm[i] = memory(a, b, c);
        for (auto x : mm[i].f) onde[x].pb(i);
    }
    for (int i = 0; i < d; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        adj[u][v] = 1;
        g[u].pb(v);
    }
    vector<ii> forb;
    for (int i = 0; i < e; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g2[u].pb(v);
        forb.pb({u, v});
    }
    vector<vector<int>> queries(m);
    for (int i = 0; i < m; ++i) {
        int tt; cin >> tt;
        queries[i].resize(tt);
        for (auto& x : queries[i]) cin >> x, --x;
    }
    vector<vector<int>> ans(m);
	bitset<100> usei, cur_closure;
    vector<bitset<100>> f_closure(100);
    vector<bitset<100>> closure(n);
    for (int i = 0; i < n_facts; ++i) adj[i][i] = 1;
    for (int k = 0; k < n_facts; ++k) for (int i = 0; i < n_facts; ++i) for (int j = 0; j < n_facts; ++j) {
        if (adj[i][k] and adj[k][j]) adj[i][j] = 1;
    }
    for (int i = 0; i < n_facts; ++i) for (int j = 0; j < n_facts; ++j) f_closure[i][j] = adj[i][j];
    for (int i = 0; i < n; ++i) {
        for (auto j : mm[i].f) closure[i] |= f_closure[j];
    }
	auto cost = [&] (int j, vector<int> x) {
		if (x.empty()) return 0.0;
		int Sj = 0, Lj = 0;
		usei = mm[x[0]].mask;
        cur_closure = closure[x[0]];
		for (auto i : x) Sj += mm[i].ri, Lj += mm[i].li, usei |= mm[i].mask, cur_closure |= closure[i];
		int Cj = 0, Mj = usei.count(), Tj = cur_closure.count(), Vj = 0;
        for (auto [u, v] : forb) if (usei[u] and usei[v]) Vj++;
		for (auto z : queries[j]) Cj += usei[z];
        double score = Sj;
        score *= (1.0 - pow((Lj/(double)l), 3));
        score *= pow((Cj/(double)sz(queries[j])), 1.5);
        score *= (1.0 - Vj/(double)Mj);
        score *= (Mj/(double)Tj);
        return score;
	};
	auto viz = [&] (vector<int>& s, bitset<1000>& mask) {
        // posso incluir um bicho ou remover um bicho
        int z = rnd(0, n-1);
        auto ss = s;
        auto m2 = mask;
        // preciso de uma forma rapida de testar vizinhanca...
        if (mask[z]) {
            for (int i = 0; i < sz(ss); ++i) {
                if (ss[i] == z) {
                    ss.erase(begin(ss)+i); break;
                }
            }
            m2[z] = 0;
        } else {
            ss.pb(z);
            m2[z] = 1;
        }
        return pair(ss, m2);
	};     

    auto random = [&] (int idx) {
        vector<int> bichos;
        for (auto j : queries[idx]) {
            int k = rnd(0, sz(onde[j]));
            if (k == sz(onde[j])) continue;
            bichos.pb(onde[j][k]);
        }
        sort(all(bichos)), bichos.erase(unique(all(bichos)), end(bichos));
        return bichos;
    };

	const double tx = 4800.0/(double)m;
    bitset<1000> cur_mask, sol_mask;
    double S = 0;
	for (int i = 0; i < m; ++i) {
		auto solution = random(i); auto s = solution;
        double opt = cost(i, solution);

        for (auto j : solution) cur_mask[j] = 1;
        sol_mask = cur_mask;

		int tries = 0, limit;

		while (get_time() <= (i+1)*tx) {
			long double t = temperature(tries, limit);
            double x = cost(i, s);
			if (ckmax(opt, x)) solution = s, sol_mask = cur_mask;
			auto [ps, ms] = viz(s, cur_mask);
			if (change(x, cost(i, ps), t)) s = ps, cur_mask = ms;
			tries++;
		}
		ans[i] = solution;
        S += cost(i, ans[i]);
	}
    S /= 100.0;
    cout << "Score: " << S << endl;
	for (int i = 0; i < m; ++i) {
		cout << sz(ans[i]) << ' ';
		for (auto x : ans[i]) cout << x + 1 << ' ';
        cout << endl;
    }
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

