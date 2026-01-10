#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
#define gato

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

int resp[100][100];

double T = 0;
void solve(int n) {
    vector<vector<int>> my(n, vector<int>(n, -1)), ruim (n, vector<int>(n, 1));
    double tot = 0;
    vector<vector<ii>> g(n+1);
    vector<vector<ii>> w(30);
    vector<vector<int>> mark(n, vector<int>(n, -1));
    auto upd = [&] () {
        for (int i = 0; i <= n; ++i) g[i].clear();
        for (int bit = 0; bit < 30; ++bit) {
            vector<int> comp(n+1, -1), z(n+1);
            for (auto [a, b] : w[bit]) g[a].pb({b, bit}), g[b].pb({a, bit});
            auto dfs = [&] (auto&& self, int u) -> void {
                for (auto [v, we] : g[u]) {
                    if (comp[v] == -1) {
                        comp[v] = comp[u], z[v] = z[u] ^ (we == bit);
                        self(self, v);
                    }
                }
            };
            for (int i = 0; i <= n; ++i) {
                if (comp[i] == -1) comp[i] = i, dfs(dfs, i);
            }
            for (int i = 0; i < n; ++i) {
                for (int j = i+1; j <= n; ++j) {
                    if (comp[i] == comp[j] and my[i][j-1] == -1) {
                        int zz = z[i] ^ z[j];
                        if (zz == 0) {
                        } else assert(bit == resp[i][j-1]), ruim[i][j-1] = 0, my[i][j-1] = bit;
                    }
                }
            }
        }
    };
    auto ask = [&] (int a, int b) {
        if (mark[a][b] != -1) return mark[a][b];
        tot += 1.0/(b-a+1);
        int x;
#ifndef gato
        cout << "? " << a+1 << ' ' << b+1 << endl;
        cin >> x;
#else
        x = resp[a][b];
#endif
        b++;
        w[x].pb({a, b});
        //g[a].pb({b, x});
        //g[b].pb({a, x});
        return mark[a][b-1] = x;
    };

    if (n == 3) {
        cout << "!" << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) cout << ask(i, j) << " \n"[j==n-1];
        }
        return;
    }
    auto solve = [&] (auto&& self, vector<int> caras) -> void {
        if (sz(caras) <= 1) return;
        // escolher 3 pontos i j k. i vai pegar ateh do n ateh o k, j vai pegar do 1 ateh o k-1
        int m = sz(caras);
        iii opt;
        double mn = inf;
        sort(all(caras));
        for (int i = 0; i < m; ++i) {
            double tt = 0;
            for (int k = 0; k < m; ++k) {
                if (i != k) tt += 1.0 / (abs(caras[k]-caras[i]));
            }
            if (ckmin(mn, tt)) opt = {i, i, -1};
            for (int j = i+1; j < m; ++j) {
                double tot = 0;
                for (int k = 0; k < m; ++k) {
                    if (i != k) tot += 1.0 / (abs(caras[k]-caras[i]));
                }
                for (int k = 0; k < m; ++k) {
                    if (i != k and k != j) tot -= 1.0 / (abs(caras[k]-caras[i]));
                    if (j != k) tot += 1.0 / (abs(caras[k]-caras[j]));

                    if (ckmin(mn, tot)) opt = {i, j, k};
                }
            }
        }
        for (auto x : caras) cout << x << ' ';
        auto [x, y, z] = opt;
        cout << endl << x << ' ' << y << ' ' << z << endl;
        if (z == -1) {
            vector<vector<int>> zz(30);
            for (auto a : caras) if (caras[x] != a) zz[ask(min(a, caras[x]), max(a, caras[x]) - 1)].pb(a);
            for (auto a : zz) self(self, a);
            return;
        }
        vector<vector<int>> zz(30);
        for (int i = 0; i < m; ++i) {
            if (i != x and i != y) {
                if (i <= z) zz[ask(min(caras[y], caras[i]), max(caras[y], caras[i])-1)].pb(caras[i]);
                else zz[ask(min(caras[x], caras[i]), max(caras[x], caras[i])-1)].pb(caras[i]);
            }
        }
        int midpoint = ask(caras[x], caras[y]-1);
        for (int i = 0; i < 30; ++i) {
            if (i <= midpoint) {
                vector<int> esq, dir;
                for (auto w : zz[i]) {
                    if (w <= z) esq.pb(w);
                    else dir.pb(w);
                }
                if (i == midpoint) {
                    esq.pb(caras[x]);
                    dir.pb(caras[y]);
                }
                self(self, esq);
                self(self, dir);
            } else {
                self(self, zz[i]);
            }
        }
    };
    vector<vector<int>> caras(30);
    for (int i = 0; i < n; ++i) caras[ask(0, i)].pb(i+1);
    for (auto x : caras) {
        cout << "TESTANDO" << endl;
        solve(solve, x);
    }
    //cout << endl;
    upd();
    cout << "gastei: " << tot << endl;
#ifndef gato
        cout << "!" << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) cout << my[i][j] << " \n"[j==n-1];
        }
#else
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (my[i][j] != resp[i][j]) {
                cout << i << " " << j << ": ";
                cout << my[i][j] << endl;
                exit(0);
            }
        }
    }
    T += tot;
#endif
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        solve(n);
    }
#else
    for (int t = 1; t <= 30; ++t) {
        int n = 100;
        vector<int> a(n);
        for (auto& x : a) x = rnd(0, (1<<30)-1);
        cout << "test " << t << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                if (i == j) resp[i][j] = a[i];
                else resp[i][j] = resp[i][j-1] ^ a[j];
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                int z = 0;
                while (resp[i][j]) resp[i][j] /= 2, z++;
                resp[i][j] = z-1;
            }
        }
        solve(n);
    }
    cout << "T = " << T << endl;
#endif
}
