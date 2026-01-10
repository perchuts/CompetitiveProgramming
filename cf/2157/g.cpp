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

int resp[100][100], SS[101], xx[100];

double T = 0;

void solve(int n) {
    vector<vector<int>> my(n, vector<int>(n, -1)), ruim (n, vector<int>(n, 1));
    double tot = 0;
    vector<vector<ii>> g(n+1), w(31);
    vector<vector<int>> mark(n, vector<int>(n, -1));
    auto upd = [&] () {
        for (int i = 0; i <= n; ++i) g[i].clear();
        for (int bit = 0; bit <= 30; ++bit) {
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
                        } else {
                            ruim[i][j-1] = 0, my[i][j-1] = bit;
                        }
                    }
                }
            }
        }
    };
    vector<int> ss(n+1);
    auto ask = [&] (int a, int b, bool flag = 0) {
        if (mark[a][b] != -1) return mark[a][b];
        if (my[a][b] != -1) return my[a][b];
        tot += 1.0/(b-a+1);
        ss[b-a+1]++;
        SS[b-a+1]++;
        int x;
#ifndef gato
        cout << "? " << a+1 << ' ' << b+1 << endl;
        cin >> x; x++;
        if (x == -1) {
            exit(0);
        }
#else
        x = resp[a][b];
#endif
        b++;
        w[x].pb({a, b});
        //g[a].pb({b, x});
        //g[b].pb({a, x});
        return mark[a][b-1] = x;
    };
    auto solve = [&] (auto&& self, vector<int> caras) -> void {
        if (sz(caras) <= 1) return;
        int x = caras[0], y = caras.back();
        int tudo = ask(x, y-1);
        vector<vector<int>> bichos(31);
        if (sz(caras) < 20) {
            vector<int> other = {x};
            for (int i = sz(caras)-1; i; --i) {
                bool flag = 0;
                double ce = 1.0/(caras[i]-x), cd = 1.0/(y-caras[i]);
                int val;
                if (ce <= cd) val = ask(x, caras[i]-1);
                else {
                    val = ask(caras[i], y-1);
                    if (val == tudo) {
                        flag = 1, other.pb(caras[i]);
                    }
                    else ckmax(val, tudo);
                }
                if (!flag) bichos[val].pb(caras[i]);
            }
            sort(all(other));
            self(self, other);
            for (auto z : other) if (x != z) bichos[my[x][z-1]].pb(z);
            for (int i = 0; i <= 30; ++i) {
                auto z = bichos[i];
                sort(all(z)), self(self, z);
            }
            upd();
        } else {
            vector<int> example(31, -1);
            example[tudo] = y;
            for (int i = sz(caras)-2; i; --i) {
                bool flag = 0;
                double ce = 1.0/(caras[i]-x), cd = 1.0/(y-caras[i]);
                int val;
                if (ce <= cd) {
                    val = ask(x, caras[i]-1);
                    if (sz(caras)-i < 3 + sz(caras)/10) ckmax(example[val], caras[i]);
                }
                else {
                    bool ok = false;
                    for (int j = 0; j <= 30; ++j) {
                        if (example[j] != -1) {
                            if (caras[i] - x >= example[j] - caras[i]) continue;
                            val = ask(caras[i], example[j]-1);
                            if (val != j) {
                                ckmax(val, j);
                                ok = 1;
                                break;
                            }
                        }
                    }
                    if (!ok) val = ask(x, caras[i]-1);
                }
                if (!flag) bichos[val].pb(caras[i]);
            }
            bichos[tudo].pb(y);
            for (auto x : bichos) {
                sort(all(x));
                self(self, x);
            }
            upd();
        }
    };
    vector<vector<int>> bichos(31);
    int tudo = ask(0, n-1);
    vector<int> example(31, -1);
    example[tudo] = n-1;
    for (int i = n-2; ~i; --i) {
        int val;
        double ce = 1.0/(i+1), cd = 1.0/(n-i+1);
        if (ce <= cd) {
            val = ask(0, i);
            if (i > 80) ckmax(example[val], i);
        }
        else {
            bool ok = 0;
            for (int j = 0; j <= 30; ++j) {
                if (example[j] != -1) {
                    val = ask(i+1, example[j]);
                    if (val != j) {
                        ckmax(val, j);
                        ok = true;
                        break;
                    }
                }
            }
            if (!ok) val = ask(0, i);
        }
        bichos[val].pb(i+1);
    }
    bichos[tudo].pb(n);
    upd();
    for (int i = 0; i <= 30; ++i) sort(all(bichos[i])), solve(solve, bichos[i]);
    upd();
    //cout << tot << endl;
    //for (int i = 1; i <= 30; ++i) cout << ss[i] << " "; cout << endl;
#ifndef gato
    cout << "!" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) cout << my[i][j]-1 << " ";
        cout << endl;
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
    if (t == 1) {
        int n; cin >> n;
        vector<vector<int>> ans(3, vector<int>(3));
        for (int i = 0; i < 3; ++i) for (int j = i; j < 3; ++j) {
            cout << "? " << i+1 << ' ' << j+1 << endl;
            cin >> ans[i][j];
        }
        cout << "!" << endl;
        for (int i = 0; i < 3; ++i) {
            for (int j = i; j < 3; ++j) cout << ans[i][j] << " \n"[j==2];
        }
        exit(0);
    }
    while(t--) {
        int n; cin >> n;
        if (n == -2) {
            exit(0);
        }
        solve(n);
    }
#else
    int tests = 50;
    int ac = 0;
    for (int w = 0; w < tests; ++w) {
        T = 0;
        for (int t = 1; t <= 30; ++t) {
            int n = 100;
            vector<int> a(n);
            for (auto& x : a) x = rnd(0, (1<<30)-1);
            //cout << "test " << t << ": ";
            xx[0] = a[0];
            for (int i = 0; i < n; ++i) {
                if (i) xx[i] = xx[i-1] ^ a[i];
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
        ac += (T <= 300);
    }
    cout << "AC: " << ac << endl;
    cout << "WA: " << tests-ac << endl;
#endif
}
