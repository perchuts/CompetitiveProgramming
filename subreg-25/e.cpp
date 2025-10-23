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

vector<ii> solve(int n, int m, vector<ii> edg) {
    vector<set<int>> g(n);
    for (auto [u, v] : edg) {
        g[u].insert(v);
        g[v].insert(u);
    }
    // identificar todos gemeos verdadeiros, removelos do grafo, repetir. posso fazer isso em nlogn
    using T = int;
    vector<int> hh(n);
    for (int i = 0; i < n; ++i) hh[i] = rnd(0, 1e18);
    vector<T> hs(n);
    map<T, set<int>> hashs;
    set<pair<int, T>> ord;
    int univ = 0;
    vector<int> eh_uni(n);
    set<ii> graus;
    for (int i = 0; i < n; ++i) {
        g[i].insert(i);
        if (sz(g[i]) == n) univ++, eh_uni[i] = true;
        else graus.insert({sz(g[i]), i});
        hs[i] = 0;
        for (auto j : g[i]) hs[i] ^= hh[j];
        hashs[hs[i]].insert(i);
    }
    for (auto [x, y] : hashs) {
        int qtd = 0;
        for (auto v : g[*begin(y)]) qtd += (y.find(v) == end(y));
        ord.insert({qtd, x});
    }
    // quero manter quantos vertices universais existem tambem
    vector<int> mark(n);
    vector<ii> ans;
    int tot = n;
    while (univ < 2 and !ord.empty()) {
        auto [fodase, zz] = *ord.begin();
        ord.erase({fodase, zz});
        auto list = hashs[zz];
#ifndef gato
        //for (auto u : list) cout << u+1 << ' ';
        //cout << endl;
#endif
        tot -= sz(list);
        for (auto u : list) assert(mark[u] == 0), mark[u] = true;
        vector<int> caras;
        for (auto v : g[*begin(list)]) if (mark[v] == 0) caras.pb(v);
        //cout << "caras: ";
        //for (auto x : caras) cout << x + 1 << ' ';
        //cout << endl;
        if (sz(caras) != fodase) return vector<ii>();
        assert(sz(caras) == fodase);
        if (sz(caras) != 2) return vector<ii>();
        int pai = caras[0], outro = caras[1];
        if (sz(g[pai]) > sz(g[outro])) swap(pai, outro);
        //cout << "Aqui: ";
        //cout << pai+1 << ' ' << outro+1 << endl;
        auto& wp = hs[pai];
        auto& wo = hs[outro];
        // o numero de caras fora eh sempre vizinhanca do bicho - numero de caras da classe de equivalencia
        if (wo == wp) return vector<ii>();
        assert(wo != wp);
        assert(sz(hashs[wo]) == sz(hashs[wp]) and sz(hashs[wp]) == 1);
        ord.erase({sz(g[outro]) - 1, wo});
        ord.erase({sz(g[pai]) - 1, wp});
        if (eh_uni[pai] == false) graus.erase({sz(g[pai]), pai});
        if (eh_uni[outro] == false) graus.erase({sz(g[outro]), outro});

        for (auto v : list) {
            if (eh_uni[v] == false) graus.erase({sz(g[v]), v});
            ans.pb({v, pai});
            g[pai].erase(v);
            g[outro].erase(v);
            wp ^= hh[v], wo ^= hh[v];
            mark[v] = true;
        }
        if (hashs[wo].empty()) ord.insert({sz(g[outro])-1, wo});
        else {
            ord.erase({sz(g[outro])-sz(hashs[wo]), wo});
            ord.insert({sz(g[outro])-sz(hashs[wo])-1, wo});
        }
        hashs[wo].insert(outro);
        if (hashs[wp].empty()) ord.insert({sz(g[pai])-1, wp});
        else {
            ord.erase({sz(g[pai])-sz(hashs[wp]), wp});
            ord.insert({sz(g[pai])-sz(hashs[wp])-1, wp});
        }
        hashs[wp].insert(pai);

        if (eh_uni[pai] == false) graus.insert({sz(g[pai]), pai});
        if (eh_uni[outro] == false) graus.insert({sz(g[outro]), outro});

        while (!graus.empty()) {
            auto [dd, z] = *prev(end(graus));
            if (dd < tot) break;
            graus.erase({dd, z});
            eh_uni[z] = true, univ++;
        }
    }
#ifndef gato
    //cout << "univ: " << univ << endl;
    //for (int i = 0; i < n; ++i) cout << eh_uni[i];
    //cout << endl;
    //for (auto [u, v] : ans) cout << u+1 << ' ' << v+1 << endl;
#endif
    auto testar = [&] () {
        for (auto& [u, v] : edg) {
            if (u > v) swap(u, v);
        }
        sort(all(edg));
        auto check = ans;
        vector<vector<int>> gg(n);
        for (auto [u, v] : ans) gg[u].pb(v), gg[v].pb(u);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < sz(gg[i]) and sz(check) <= sz(edg); ++j) {
                for (int k = j + 1; k < sz(gg[i]) and sz(check) <= sz(edg); ++k) {
                    check.pb({gg[i][j], gg[i][k]});
                }
            }
        }
        for (auto& [u, v] : check) if (u > v) swap(u, v);
        sort(all(check));
        return check == edg;
    };
    if (!ord.empty()) {
        assert(univ != 0);
        vector<int> uni;
        for (int i = 0; i < n; ++i) if (sz(g[i]) == tot and mark[i] == 0) uni.pb(i);
        if (sz(uni) != univ) return vector<ii>();
        assert(sz(uni) == univ);
        if (univ == tot) {
            // estrela (diam <= 2)
            for (int i = 1; i < sz(uni); ++i) ans.pb({uni[0], uni[i]});
        } else if (univ == 2) {
            // troço (diam = 3)
            int u = uni[0], v = uni[1];
            auto checkpoint = ans;
            for (int __ = 0; __ < 2; ++__) {
                ans = checkpoint;
                ans.pb({u, v});
                mark[u] = mark[v] = true;
                int bicho1 = 0;
                for (int i = 0; i < n; ++i) {
                    if (mark[i]) continue;
                    bicho1 = i; break;
                }
                for (int i = 0; i < n; ++i) {
                    if (mark[i]) continue;
                    if (g[i] == g[bicho1]) ans.pb({i, (__ ? u : v)});
                    else ans.pb({i, (__ ? v : u)});
                }
                if (testar()) return ans;
            }
            return vector<ii>();
        } else return vector<ii>();
    }
    if (!testar()) return vector<ii>();
    // verificar se oq eu to cuspindo eh true
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<ii> edg(m);
        for (auto& [x, y] : edg) cin >> x >> y, --x, --y;
        auto ans = solve(n, m, edg);
        for (auto [u, v] : ans) cout << u+1 << ' ' << v+1 << endl;
        if (ans.empty()) cout << "*" << endl;
    }
#else
    int t = 1;
    while (true) {
        int tipo = rnd(1, 10);
        tipo = (tipo >= 9);
        int n = rnd(3, 50);
        vector<ii> edg;
        vector<vector<int>> adj(n, vector<int>(n));
        vector<int> p(n); iota(all(p), 0); shuffle(all(p), rng);
        for (int i = 1; i < n; ++i) {
            int pp = rnd(0, i-1);
            adj[p[pp]][p[i]] = adj[p[i]][p[pp]] = true;
            edg.pb({p[pp], p[i]});
        }
        if (tipo) {
            int m = rnd(n-1, n*(n-1)/2);
            while (sz(edg) != m) {
                int u = rnd(0, n-2), v = rnd(u+1, n-1);
                while (adj[u][v]) u = rnd(0, n-2), v = rnd(u+1, n-1);
                adj[u][v] = adj[v][u] = true;
                edg.pb({u, v});
            }
        } else {
            auto temp = adj;
            for (int i = 0; i < n; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    if (adj[i][j]) continue;
                    bool ok = false;
                    for (int k = 0; k < n; ++k) {
                        if (temp[i][k] and temp[k][j]) { ok = true; break; }
                    }
                    if (ok) edg.pb({i, j}), adj[i][j] = adj[j][i] = true;
                }
            }
        }
        //cout << "case = " << tipo << endl;
        //cout << n << ' ' << sz(edg) << endl;
        //for (auto [u, v] : edg) cout << u + 1 << ' ' << v + 1 << endl;
        auto ans = solve(n, sz(edg), edg);
        if (tipo == 0 and ans.empty()) {
            cout << "Wrong answer on test " << t << endl;
            cout << "case = " << tipo << endl;
            cout << n << ' ' << sz(edg) << endl;
            for (auto [u, v] : edg) cout << u + 1 << ' ' << v + 1 << endl;
            cout << "Could not find a certificate but there is one" << endl;
            exit(0);
        }
        if (!ans.empty()) {
            vector<vector<int>> aa(n, vector<int>(n));
            for (auto [u, v] : ans) aa[u][v] = aa[v][u] = true;
            auto aa2 = aa;
            for (int i = 0; i < n; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    if (aa[i][j]) continue;
                    bool ok = false;
                    for (int k = 0; k < n; ++k) {
                        if (aa[i][k] and aa[k][j]) { ok = true; break; }
                    }
                    if (ok) aa2[i][j] = aa2[j][i] = true;
                }
            }
            if (aa2 != adj) {
                cout << "Wrong answer on test " << t << endl;
                cout << "case = " << tipo << endl;
                cout << n << ' ' << sz(edg) << endl;
                for (auto [u, v] : edg) cout << u + 1 << ' ' << v + 1 << endl;
                cout << "Certificate is incorrect: " << endl;
                for (auto [u, v] : ans) cout << u + 1 << ' ' << v + 1 << endl;
                cout << "Your certificate: " << endl;
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        cout << aa2[i][j] << " \n"[j==n-1];
                    }
                }
                cout << endl;
                cout << "Original adj. matrix: " << endl;
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        cout << adj[i][j] << " \n"[j==n-1];
                    }
                }
                exit(0);
            }
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
