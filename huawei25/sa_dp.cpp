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


const double a = 0.9999;

double last = 1e9;
const int TRIES = 5000;
// double eps = 1e-8;

double temperature(int tries, int limit) { return last *= a; }


bool change(int x, int y, double t) {
      if (y > x) return true;
      double p = exp((y - x) / t), k = rnd_d(0, 1);
      return p >= k;
}

bool adj[100][100];

int dp[1001][33768];
bool tr[1001][33768];

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
            for (int i = 0; i < 100; ++i) mask[i] = 0;
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
    double sc_sum = 0;
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
    vector<int> bad(100);
	auto cost = [&] (int j, vector<int> x) {
		if (x.empty()) return 0.0;
		int Sj = 0, Lj = 0;
		usei = mm[x[0]].mask;
        cur_closure = closure[x[0]];
		for (auto i : x) Sj += mm[i].ri, Lj += mm[i].li, usei |= mm[i].mask, cur_closure |= closure[i];
        if (Lj > l) return 0.0;
		int Cj = 0, Mj = usei.count(), Tj = cur_closure.count(), Vj = 0;
        for (auto [u, v] : forb) if (usei[u] and usei[v]) bad[u] = bad[v] = 1;
        for (int i = 0; i < 100; ++i) Vj += bad[i], bad[i] = 0;
		for (auto z : queries[j]) Cj += usei[z];
        double score = Sj;
        score *= (1.0 - pow((Lj/(double)l), 3.0));
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
    vector<int> caras;
    vector<int> valid;
    auto random = [&] (int idx) {
        int opt = valid[rnd(0, sz(valid)-1)];
        int i = sz(caras);
        vector<int> bichos;
        for (; i; --i) {
            if (tr[i][opt]) bichos.pb(caras[i-1]), opt -= mm[caras[i-1]].li;
        }
        return bichos;
    };

	const double tx = 4950.0/(double)m;
    bitset<1000> cur_mask, sol_mask;
	for (int idq = 0; idq < m; ++idq) {
        valid.clear();
        caras.clear();
        valid.pb(0);
        vector<int> caras;
        for (auto x : queries[idq]) {
            for (auto z : onde[x]) caras.pb(z);
        }
        sort(all(caras)), caras.erase(unique(all(caras)), end(caras));
        for (int i = 1; i <= sz(caras); ++i) {
            int bicho = caras[i-1];
         int li = mm[bicho].li;
         int ri = mm[bicho].ri;
            for (int j = 0; j < l; ++j) {
                dp[i][j] = dp[i-1][j];
                tr[i][j] = 0;
                if (j >= li and dp[i][j] < dp[i-1][j-li] + ri) dp[i][j] = dp[i-1][j-li] + ri, tr[i][j] = 1;
            }
        }
        for (int i = 1; i < l; ++i) if( dp[sz(caras)][i] != 0) valid.pb(i);

        auto iteration = [&] () {
            auto solution = random(idq); auto s = solution;
            double opt = cost(idq, solution);

            for (auto j : solution) cur_mask[j] = 1;
            sol_mask = cur_mask;

            int tries = 0, limit;
            // roda ateh estabilizar
            while (tries < TRIES) {
                long double t = temperature(tries, limit);
                double x = cost(idq, s);
                if (ckmax(opt, x)) solution = s, sol_mask = cur_mask;
                // por 30% do tempo eu vou explorar pra cacete
                auto [ps, ms] = viz(s, cur_mask);
                if (change(x, cost(idq, ps), t)) s = ps, cur_mask = ms;
                tries++;
            }
            return solution;
        };
        double ini = get_time();
        ans[idq] = iteration();
        double fim = get_time();
        double taken = fim - ini;
        double opt = cost(idq, ans[idq]);
        while (get_time() + taken <= (idq+1) * tx) {
            auto sexo = iteration();
            if (ckmax(opt, cost(idq, sexo))) ans[idq] = sexo;
        }
	}
    sc_sum = 0;
	for (int i = 0; i < m; ++i) {
		cout << sz(ans[i]) << ' ';
		for (auto x : ans[i]) cout << x + 1 << ' ';
        cout << endl;
        sc_sum += cost(i, ans[i]);
    }
    sc_sum /= 100.0;
    //cout << sc_sum << endl;
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

